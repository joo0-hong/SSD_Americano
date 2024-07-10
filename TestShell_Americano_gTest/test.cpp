#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../TestShell_Americano/TestShell.cpp"
#include "../TestShell_Americano/FileReader.cpp"
#include "../TestShell_Americano/SSDDriver.cpp"
#include "../TestShell_Americano/CheckCommand.cpp"

using namespace std;
using namespace testing;

class FileReaderMock : public FileReader {
public:
	FileReaderMock(string filePath)
		: FileReader{ filePath } {}

	MOCK_METHOD(string, readFile, (), (override));
};

class SSDDriverMock : public SSDDriver {
public:
	SSDDriverMock(const string& ssdPath)
		: SSDDriver{ ssdPath } {}

	MOCK_METHOD(void, write, (const string& lba, const string& data), (const override));
	MOCK_METHOD(void, read, (const string& lba), (const override));
};

class TestShellFixture : public testing::Test {
public:
	const string SSD_PATH = "..\\x64\\Debug\\SSDMock";
	const string RESULT_PATH = "..\\resources\\result.txt";
	
	const int LBA_MIN = 0;
	const int LBA_MAX = 100;

	SSDDriverMock ssdDriverMk{ SSD_PATH };
	FileReaderMock fileReaderMk{ RESULT_PATH };
	TestShell app{ &ssdDriverMk, &fileReaderMk };
};

TEST_F(TestShellFixture, Read_InvalidLBA) {
	//arrange
	EXPECT_CALL(fileReaderMk, readFile)
		.WillRepeatedly(Return("NULL"));

	EXPECT_CALL(ssdDriverMk, read)
		.Times(2);

	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());

	//action
	string LBA{ "-1" };
	app.read(LBA);

	LBA = "abcd";
	app.read(LBA);

	std::cout.rdbuf(oldCoutStreamBuf);	// 기존 buf 복원

	string expect = "NULL\nNULL\n";
	string actual = oss.str();

	//assert
	EXPECT_EQ(expect, actual);

}
TEST_F(TestShellFixture, Read_ValidLBA) {
	//arrange
	EXPECT_CALL(fileReaderMk, readFile)
		.WillRepeatedly(Return("0x12341234"));

	EXPECT_CALL(ssdDriverMk, read)
		.Times(1);

	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());

	//action
	string LBA{ "0" };
	app.read(LBA);

	std::cout.rdbuf(oldCoutStreamBuf);	// 기존 buf 복원

	string expect = "0x12341234\n";
	string actual = oss.str();

	//assert
	EXPECT_EQ(expect, actual);
}

TEST_F(TestShellFixture, Write_Pass) {
	string LBA("1");
	string data("0x1298CDEF");
}
TEST_F(TestShellFixture, Write) {
	EXPECT_CALL(ssdDriverMk, write)
		.Times(1);

	app.write("1", "0x1298CDEF");
}

TEST_F(TestShellFixture, FullRead) {
	EXPECT_CALL(fileReaderMk, readFile)
		.Times(LBA_MAX)
		.WillRepeatedly(Return("0x12341234"));

	EXPECT_CALL(ssdDriverMk, read)
		.Times(LBA_MAX);

	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());

	app.fullread();

	string expect = "";

	for (int i = LBA_MIN; i < LBA_MAX; i++) {
		expect += "0x12341234\n";
	}

	string actual = oss.str();
	std::cout.rdbuf(oldCoutStreamBuf);	// 기존 buf 복원

	//assert
	EXPECT_EQ(expect, actual);
}

TEST_F(TestShellFixture, FullWrite) {
	EXPECT_CALL(ssdDriverMk, write)
		.Times(LBA_MAX);

	app.fullwrite("0xABCDFFF");
}

TEST_F(TestShellFixture, Help) {
	app.help();
}

TEST_F(TestShellFixture, TestApp1) {
	//arrange
	EXPECT_CALL(ssdDriverMk, write)
		.Times(LBA_MAX);

	EXPECT_CALL(ssdDriverMk, read)
		.Times(LBA_MAX);

	EXPECT_CALL(fileReaderMk, readFile)
		.Times(LBA_MAX)
		.WillRepeatedly(Return("0x11111111"));

	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());

	//action
	app.testapp1("0x11111111");

	std::cout.rdbuf(oldCoutStreamBuf);	// 기존 buf 복원

	//assert
	string expect = "";
	for (int i = LBA_MIN; i < LBA_MAX; ++i) {
		expect += "0x11111111\n";
	}
	string actual = oss.str();

	EXPECT_EQ(expect, actual);
}

TEST_F(TestShellFixture, TestApp2) {
	//arrange
	EXPECT_CALL(fileReaderMk, readFile)
		.Times(AtLeast(1))
		.WillRepeatedly(Return("0x12345678"));

	EXPECT_CALL(ssdDriverMk, read)
		.Times(AtLeast(1));
	EXPECT_CALL(ssdDriverMk, write)
		.Times(AtLeast(1));

	//action
	bool actual = app.testApp2();

	//assert
	EXPECT_EQ(true, actual);
}

TEST_F(TestShellFixture, erase) {
	app.erase("0", "1");

}

TEST(CheckCommand, CheckCommand_InvalidCommand_r) {
	string test_input = "r";
	string arg1, arg2;

	CheckCommand checker;

	EXPECT_EQ(-1, checker.checkCmd(test_input, arg1, arg2));
}


TEST(CheckCommand, CheckCommand_InvalidCommand_NoCommand) {
	string test_input = " ";
	string arg1, arg2;

	CheckCommand checker;

	EXPECT_EQ(-1, checker.checkCmd(test_input, arg1, arg2));
}

TEST(CheckCommand, CheckCommand_read_ValidLBA_0) {
	string test_input = "read 0";
	string arg1, arg2;

	CheckCommand checker;

	EXPECT_EQ(0x1, checker.checkCmd(test_input, arg1, arg2));
}

TEST(CheckCommand, CheckCommand_read_InvalidLBA_NotNumber_r) {
	string test_input = "read r";
	string arg1, arg2;

	CheckCommand checker;
	
	EXPECT_EQ(-2, checker.checkCmd(test_input, arg1, arg2));
}

TEST(CheckCommand, CheckCommand_read_InvalidLBA_NotNumber_0x10) {
	string test_input = "read 0x10";
	string arg1, arg2;

	CheckCommand checker;

	EXPECT_EQ(-2, checker.checkCmd(test_input, arg1, arg2));
}

TEST(CheckCommand, CheckCommand_read_InvalidLBA_NotNumber_A) {
	string test_input = "read A";
	string arg1, arg2;

	CheckCommand checker;

	EXPECT_EQ(-2, checker.checkCmd(test_input, arg1, arg2));
}

TEST(CheckCommand, CheckCommand_read_InvalidLBA_OutOfRange_minus1) {
	string test_input = "read -1";
	string arg1, arg2;

	CheckCommand checker;

	EXPECT_EQ(-2, checker.checkCmd(test_input, arg1, arg2));

}

TEST(CheckCommand, CheckCommand_read_InvalidLBA_OutOfRange_101) {
	string test_input = "read 101";
	string arg1, arg2;

	CheckCommand checker;

	EXPECT_EQ(-2, checker.checkCmd(test_input, arg1, arg2));
}

TEST(CheckCommand, CheckCommand_write_ValidData_0x12345678) {
	string test_input = "write 1 0x12345678";
	string arg1, arg2;

	CheckCommand checker;

	EXPECT_EQ(0x0, checker.checkCmd(test_input, arg1, arg2));
}

TEST(CheckCommand, CheckCommand_write_InvalidData_NoPrefix_12345678) {
	string test_input = "write 1 12345678";
	string arg1, arg2;

	CheckCommand checker;

	EXPECT_EQ(-2, checker.checkCmd(test_input, arg1, arg2));
}

TEST(CheckCommand, CheckCommand_write_InvalidData_Not10digit_0x1234) {
	string test_input = "write 1 0x1234";
	string arg1, arg2;

	CheckCommand checker;

	EXPECT_EQ(-2, checker.checkCmd(test_input, arg1, arg2));
}

TEST(CheckCommand, CheckCommand_write_InvalidData_NotNumber_0xABCDEFGH) {
	string test_input = "write 1 0xABCDEFGH";
	string arg1, arg2;

	CheckCommand checker;

	EXPECT_EQ(-2, checker.checkCmd(test_input, arg1, arg2));
}

TEST(CheckCommand, CheckCommand_write_InvalidData_NotNumber_r) {
	string test_input = "write 1 r";
	string arg1, arg2;

	CheckCommand checker;

	EXPECT_EQ(-2, checker.checkCmd(test_input, arg1, arg2));
}
