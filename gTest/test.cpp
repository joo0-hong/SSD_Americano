#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD_Americano/NandInterface.h"
#include "../SSD_Americano/HostInterface.cpp"

using namespace testing;

class MockedNand : public NANDInterface {
public:
    MOCK_METHOD(void, read, (int lba), (override));
    MOCK_METHOD(void, write, (int lba, int data), (override));
};

TEST(SSDTest, NANDInterface) {
    MockedNand nand;

    EXPECT_CALL(nand, read(_)).Times(1);
    EXPECT_CALL(nand, write(_, _)).Times(1);

    nand.read(0);
    nand.write(0, 0);
}

TEST(HostInterfaceTest, ParsingInputArgs) {
	char exe[] = "TESTFILE.exe";
	char a = 'W';
	int adddr = 3;
	int data = 0x1298cdef;
	char* argv[] = { exe, &a, (char*)&adddr, (char*)&data };

	HostInterface hostIntf;
	hostIntf.ParseCommand(4, argv);

	EXPECT_EQ(WRITE, hostIntf.getCmd());
	EXPECT_EQ(adddr, hostIntf.getAddr());
	EXPECT_EQ(data, hostIntf.getData());
}

TEST(HostInterfaceTest, CheckingValidWriteCommands) {
	char exe[] = "TESTFILE.exe";
	char* a = "W";
	char* adddr = "3";
	char* data = "0x1298cdef";
	char* argv[] = { exe, a, adddr, data };

	HostInterface hostIntf;
	bool result = hostIntf.checkInvalidCommand(4, argv);

	EXPECT_EQ(false, result);
}

TEST(HostInterfaceTest, CheckingValidReadCommands) {
	char exe[] = "TESTFILE.exe";
	char* a = "R";
	char* adddr = "3";
	char* argv[] = { exe, a, adddr};

	HostInterface hostIntf;
	bool result = hostIntf.checkInvalidCommand(3, argv);

	EXPECT_EQ(false, result);
}


TEST(HostInterfaceTest, CheckingInvalidLBA) {
	char exe[] = "TESTFILE.exe";
	char* a = "W";
	char* adddr = "111";
	char* data = "0x1298cdef";
	char* argv[] = { exe, a, adddr, data };

	HostInterface hostIntf;
	bool result = hostIntf.checkInvalidCommand(4, argv);

	EXPECT_EQ(true, result);
}