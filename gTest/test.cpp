#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD_Americano/NandInterface.h"
#include "../SSD_Americano/HostInterface.h"
#include "../SSD_Americano/Nand.h"

using namespace testing;

enum hostArguIndex {
	IDX_EXE_FILE = 0,
	IDX_COMMAND,
	IDX_ADDRESS,
	IDX_DATA,
	IDX_MAX = IDX_DATA,
};

class MockedNand : public NANDInterface {
public:
	MOCK_METHOD(void, read, (int lba), (override));
	MOCK_METHOD(void, write, (int lba, string data), (override));
	MOCK_METHOD(void, erase, (int lba, string size), (override));
	MOCK_METHOD(void, error, (), (override));
};

class HostIntfTestFixture : public testing::Test {
public:
	void SetUp() {
		argv[IDX_EXE_FILE] = "TESTFILE.exe";
	}
	void SetNormalWrite() {
		argv[IDX_COMMAND] = "W";
		argv[IDX_ADDRESS] = "3";
		argv[IDX_DATA] = "0xFFFFFFFF";
	}
	void SetNormalRead() {
		argv[IDX_COMMAND] = "R";
		argv[IDX_ADDRESS] = "3";
	}
	void SetNormalErase() {
		argv[IDX_COMMAND] = "E";
		argv[IDX_ADDRESS] = "3";
	}

	NiceMock<MockedNand> nand;
	HostInterface hostIntf{ &nand };
	char* argv[IDX_MAX] = {};
private:
	const int VALID_WRITE_IDX_NUM = 4;
	const int VALID_READ_IDX_NUM = 3;
};

TEST(SSDTest, NANDInterface) {
	NiceMock<MockedNand> nand;

    EXPECT_CALL(nand, read(_)).Times(1);
    EXPECT_CALL(nand, write(_, _)).Times(1);
	EXPECT_CALL(nand, erase(_, _)).Times(1);

	nand.read(0);
	nand.write(0, " ");
	nand.erase(0, " ");
}

TEST_F(HostIntfTestFixture, CheckingInvalidArgumentNum) {
	SetNormalWrite();

	bool result = hostIntf.checkInvalidCommand(2, argv);

	EXPECT_EQ(true, result);
}

TEST_F(HostIntfTestFixture, CheckingValidWriteCommands) {
	SetNormalWrite();

	bool result = hostIntf.checkInvalidCommand(4, argv);

	EXPECT_EQ(false, result);
}

TEST_F(HostIntfTestFixture, CheckingValidReadCommands) {
	SetNormalRead();

	bool result = hostIntf.checkInvalidCommand(3, argv);

	EXPECT_EQ(false, result);
}

TEST_F(HostIntfTestFixture, CheckingInvalidLBA) {
	SetNormalWrite();
	argv[IDX_ADDRESS] = "111";

	bool result = hostIntf.checkInvalidCommand(4, argv);

	EXPECT_EQ(true, result);
}

TEST_F(HostIntfTestFixture, CheckingInvalidData) {
	SetNormalWrite();
	argv[IDX_DATA] = "0x1298CDEW";

	bool result = hostIntf.checkInvalidCommand(4, argv);

	EXPECT_EQ(true, result);
}

TEST_F(HostIntfTestFixture, StartWriteCmd) {
	SetNormalWrite();

	EXPECT_CALL(nand, write(_, _)).Times(1);

	hostIntf.processCommand(4, argv);
}

TEST_F(HostIntfTestFixture, StartReadCmd) {
	SetNormalRead();

	EXPECT_CALL(nand, read(_)).Times(1);

	hostIntf.processCommand(3, argv);
}

TEST_F(HostIntfTestFixture, dataStringCheck) {
	SetNormalWrite();
	argv[IDX_DATA] = "0x1298dead";

	EXPECT_EQ(true, hostIntf.checkInvalidCommand(4, argv));
}

TEST_F(HostIntfTestFixture, WrongCommandNameCheck) {
	SetNormalWrite();
	argv[IDX_DATA] = "0x1298dead";

	EXPECT_CALL(nand, error()).Times(1);

	hostIntf.processCommand(4, argv);
}

TEST_F(HostIntfTestFixture, CheckingValidEraseCommand) {
	SetNormalErase();
	argv[IDX_DATA] = "10";

	bool result = hostIntf.checkInvalidCommand(4, argv);

	EXPECT_EQ(false, result);
}

TEST_F(HostIntfTestFixture, CheckingInvalidEraseSize) {
	SetNormalErase();
	argv[IDX_DATA] = "1A";

	bool result = hostIntf.checkInvalidCommand(4, argv);

	EXPECT_EQ(true, result);
}

TEST_F(HostIntfTestFixture, CheckingInvalidEraseArguementNum) {
	SetNormalErase();
	argv[IDX_DATA] = "5";

	bool result = hostIntf.checkInvalidCommand(3, argv);

	EXPECT_EQ(true, result);
}

TEST(NANDTest, NANDWriteRead) {
	NAND nand{ "TestNand.txt", "TestResult.txt" };

	nand.write(3, "0x1298DEAD");
	nand.read(3);
}

TEST(NANDTest, NANDError) {
	NAND nand{ "TestNand.txt", "TestResult.txt" };

	nand.error();
}

TEST(NANDTest, NANDEraseTooLargeSize) {
	NAND nand{ "TestNand.txt", "TestResult.txt" };
	int lba = 0;
	string eraseSize = "20";

	nand.write(3, "0x1298DEAD");
	nand.write(13, "0x1298DEAD");
	nand.erase(0, eraseSize);
}

TEST(NANDTest, NANDEraseSmallLeftSize) {
	NAND nand{ "TestNand.txt", "TestResult.txt" };
	string eraseSize = "5";

	nand.write(99, "0x1298DEAD");
	nand.erase(98, eraseSize);
}