#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../TestShell_Americano/TestShell.cpp"

using namespace std;

TEST(TestShell, TestShellWriteFail_LBA_GreaterThanMax) {
	string ssd_path = "..\\x64\\Debug\\SSDMock";
	string result_path = ""

	TestShell ts(ssd_path, result_path);
	string LBA("1");
	string data("0x1298CDEF");

	ts.write(LBA, data);
}