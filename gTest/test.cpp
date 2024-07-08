#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD_Americano/hostInterface.cpp"

TEST(HostInterfaceTest, ParsingInputArgs) {
	char exe[] = "TESTFILE.exe";
	char a = 'W';
	int adddr = 3;
	int data = 0x1298cdef;
	char* argv[] = {exe, &a, (char*)&adddr, (char*)&data};
	
	HostInterface hostIntf;
	hostIntf.ParseCommand(4, argv);

	EXPECT_EQ(WRITE, hostIntf.getCmd());
	EXPECT_EQ(adddr, hostIntf.getAddr());
	EXPECT_EQ(data, hostIntf.getData());
}