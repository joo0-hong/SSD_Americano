#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../TestShell_Americano/TestShell.cpp"
#include "../TestShell_Americano/FileReader.cpp"
#include "../TestShell_Americano/SSDDriver.cpp"

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

	MOCK_METHOD(void, write, (string lba, string data), (override));
	MOCK_METHOD(void, read, (string lba), (override));
};

class TestShellFixture : public testing::Test {
public:
	const string SSD_PATH = "..\\x64\\Debug\\SSDMock";
	const string RESULT_PATH = "..\\resources\\result.txt";
	
	FileReaderMock mk{ RESULT_PATH };
	TestShell app{ SSD_PATH, &mk };
};

// Parser 테스트수트~~~

TEST_F(TestShellFixture, Read_InvalidLBA) {
	//arrange
	EXPECT_CALL(mk, readFile)
		.WillRepeatedly(Return("NULL"));

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
	EXPECT_CALL(mk, readFile)
		.WillRepeatedly(Return("0x12341234"));

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
	app.write("1", "0x1298CDEF");
}

TEST_F(TestShellFixture, FullRead) {
	app.fullread();
}

TEST_F(TestShellFixture, FullWrite) {
	app.fullwrite("0xABCDFFF");
}

TEST_F(TestShellFixture, Help) {
	app.help();
}