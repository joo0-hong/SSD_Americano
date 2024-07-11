#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Command.h"
#include "TestShell.h"
#include "ScenarioParser.h"

using namespace std;

enum class Test {

	TEST_COMMAND = 0,
	TEST_RUNNER = 1,
	TEST_SCENARIO = 2
};

class HostInterface {
public:
	HostInterface(TestShell* shell) : app(shell) { }
	int checkTestType(string input);

	bool processScenario(ScenarioParser& scenario);
	bool processRunner(ifstream& file_read);
	bool processCommand(string input, std::vector<std::string> expect_v = {});

	int checkCmd(string input, string& arg1, string& arg2);

private:
	TestShell* app;

	vector<string> split(string input);	
	bool isValidLBA(string arg);
	bool is_xdigits(const std::string& str);
	bool isValidData(string arg);
	bool isValidSize(string arg);
	bool isValidRange(string arg1, string arg2);

	const int MIN_LBA = 0;
	const int MAX_LBA = 99;
	const int INPUT_COMMAND = 1;
	const int INPUT_COMMAND_ARG1 = 2;
	const int INPUT_COMMAND_ARG1_ARG2 = 3;

};
