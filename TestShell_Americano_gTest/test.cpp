#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../TestShell_Americano/TestShell.cpp"

using namespace std;

class TestShellFixture : public testing::Test {
public:
	const std::string SSD_PATH = "..\\x64\\Debug\\SSDMock";
	const std::string RESULT_PATH = "..\\resources\\result.txt";

	TestShell app{ SSD_PATH, RESULT_PATH };
};

TEST_F(TestShellFixture, Read_InvalidCommand) {
	
	app.read("-1");
	app.read("dsaf");
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