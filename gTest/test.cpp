#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD_Americano/NandInterface.h"
#include "../SSD_Americano/HostInterface.cpp"

using namespace testing;

class MockedNand : public NANDInterface {
public:
    MOCK_METHOD(void, read, (int lba), (override));
	MOCK_METHOD(void, write, (int lba, string data), (override));
	MOCK_METHOD(void, error, (), (override));
};

class HostIntfTestFixture : public testing::Test {
public :
	NiceMock<MockedNand> nand;
	HostInterface hostIntf{ &nand };
};

TEST(SSDTest, NANDInterface) {
	NiceMock<MockedNand> nand;

    EXPECT_CALL(nand, read(_)).Times(1);
    EXPECT_CALL(nand, write(_, _)).Times(1);

    nand.read(0);
	nand.write(0, " ");
}

TEST_F(HostIntfTestFixture, CheckingInvalidArgumentNum) {
	char exe[] = "TESTFILE.exe";
	char* a = "W";
	char* adddr = "3";
	char* data = "0x1298CDEF";
	char* argv[] = { exe, a, adddr, data };

	bool result = hostIntf.checkInvalidCommand(2, argv);

	EXPECT_EQ(true, result);
}

TEST_F(HostIntfTestFixture, CheckingValidWriteCommands) {
	char exe[] = "TESTFILE.exe";
	char* a = "W";
	char* adddr = "3";
	char* data = "0x1298CDEF";
	char* argv[] = { exe, a, adddr, data };

	bool result = hostIntf.checkInvalidCommand(4, argv);

	EXPECT_EQ(false, result);
}

TEST_F(HostIntfTestFixture, CheckingValidReadCommands) {
	char exe[] = "TESTFILE.exe";
	char* a = "R";
	char* adddr = "3";
	char* argv[] = { exe, a, adddr};

	bool result = hostIntf.checkInvalidCommand(3, argv);

	EXPECT_EQ(false, result);
}

TEST_F(HostIntfTestFixture, CheckingInvalidLBA) {
	char exe[] = "TESTFILE.exe";
	char* a = "W";
	char* adddr = "111";
	char* data = "0x1298CDEF";
	char* argv[] = { exe, a, adddr, data };

	bool result = hostIntf.checkInvalidCommand(4, argv);

	EXPECT_EQ(true, result);
}

TEST_F(HostIntfTestFixture, CheckingInvalidData) {
	char exe[] = "TESTFILE.exe";
	char* a = "W";
	char* adddr = "3";
	char* data = "0x1298CDEW";
	char* argv[] = { exe, a, adddr, data };

	bool result = hostIntf.checkInvalidCommand(4, argv);

	EXPECT_EQ(true, result);
}

TEST_F(HostIntfTestFixture, StartWriteCmd) {
	char exe[] = "TESTFILE.exe";
	char* a = "W";
	char* adddr = "3";
	char* data = "0x1298CDEF";
	char* argv[] = { exe, a, adddr, data };

	EXPECT_CALL(nand, write(_, _)).Times(1);

	hostIntf.processCommand(4, argv);
}

TEST_F(HostIntfTestFixture, StartReadCmd) {
	char exe[] = "TESTFILE.exe";
	char* a = "R";
	char* adddr = "3";
	char* argv[] = { exe, a, adddr };

	EXPECT_CALL(nand, read(_)).Times(1);

	hostIntf.processCommand(3, argv);
}

TEST_F(HostIntfTestFixture, dataStringCheck) {
	char exe[] = "TESTFILE.exe";
	char* a = "W";
	char* adddr = "3";
	char* data = "0x1298dead";
	char* argv[] = { exe, a, adddr, data };

	EXPECT_EQ(true, hostIntf.checkInvalidCommand(4, argv));
}

TEST_F(HostIntfTestFixture, WrongCommandNameCheck) {
	char exe[] = "TESTFILE.exe";
	char* a = "WRITE";
	char* adddr = "3";
	char* data = "0x1298dead";
	char* argv[] = { exe, a, adddr, data };

	EXPECT_CALL(nand, error()).Times(1);

	hostIntf.processCommand(4, argv);
}

