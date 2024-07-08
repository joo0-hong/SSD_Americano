#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../TestShell_Americano/TestShell.cpp"

using namespace std;

TEST(TestShell, Read_InvalidCommand) {
	const std::string SSD_PATH = "..\\x64\\Debug\\SSDMock";
	const std::string RESULT_PATH = "..\\resources\\result.txt";

	TestShell app(SSD_PATH, RESULT_PATH);

	app.read("-1");
	app.read("dsaf");
}

TEST(TestShell, TestShellWriteFail_LBA_GreaterThanMax) {
	string ssd_path = "..\\x64\\Debug\\SSDMock";
	string result_path = "..\\x64\\Debug\\resources\\result.txt";

	TestShell ts(ssd_path, result_path);
	string LBA("1");
	string data("0x1298CDEF");

	ts.write(LBA, data);
}