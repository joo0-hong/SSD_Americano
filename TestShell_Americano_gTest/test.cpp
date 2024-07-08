#include <string>

#include "gmock/gmock.h"

#include "../TestShell_Americano/TestShell.cpp"

TEST(TestShell, Read_InvalidCommand) {
	const std::string SSD_PATH = "..\\x64\\Debug\\SSDMock";
	const std::string RESULT_PATH = "..\\resources\\result.txt";
	
	TestShell app(SSD_PATH, RESULT_PATH);
	
	app.read("-1");
	app.read("dsaf");
}