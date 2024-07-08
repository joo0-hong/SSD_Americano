#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../TestShell_Americano/TestShell.cpp"

using namespace std;

TEST(TestShell, TestShellWriteFail_LBA_GreaterThanMax) {
	TestShell ts("..\\x64\\Debug\\SSDMock ");
	string data("1");
	string LBA("0x1298CDEF");

	ts.write(LBA, data);
}