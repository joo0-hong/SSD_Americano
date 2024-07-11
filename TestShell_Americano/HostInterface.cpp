#include "HostInterface.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int HostInterface::checkTestType(string input) {
	string arg1, arg2;

	if (checkCmd(input, arg1, arg2) == static_cast<int>(Command::RUNNER)) {
		return static_cast<int>(Test::TEST_RUNNER);
	}

	if (checkCmd(input, arg1, arg2) == static_cast<int>(Command::SCENARIO)) {
		return static_cast<int>(Test::TEST_SCENARIO);;
	}

	return static_cast<int>(Test::TEST_COMMAND);
}


bool HostInterface::processRunner(ifstream& file_read) {

	vector<string> file_str;
	string line;

	app->setscenariomode(true);

	while (getline(file_read, line)) {
		file_str.push_back(line);
	}

	for (vector<string>::iterator iter = file_str.begin(); iter != file_str.end(); iter++) {
		std::cout << *iter << " --- " << "Run" << " ... ";
		string result = app ->run(*iter) == true ? "Pass" : "Fail";
		std::cout << result << std::endl;
	}
	app->setscenariomode(false);

	return true;
}


bool HostInterface::processScenario(ScenarioParser & scenario) {

	app->setscenariomode(true);

	scenario.test();	

	//TODO: call processCommand

	app->setscenariomode(false);

	return true;
}

bool HostInterface::processCommand(string input, std::vector<std::string> expect_v) {
	
	string arg1, arg2;
	int cmd = checkCmd(input, arg1, arg2);
	bool result = false;
	
	switch (cmd) {
	case static_cast<int>(Command::WRITE):
		result = app->runCommand("write", arg1, arg2, expect_v);
		break;
	case static_cast<int>(Command::READ):
		result = app->runCommand("read", arg1, arg2, expect_v);
		break;
	case static_cast<int>(Command::EXIT):
		result = false;
		break;
	case static_cast<int>(Command::HELP):
		result = app->runCommand("help", arg1, arg2, expect_v);
		break;
	case static_cast<int>(Command::FULLWRITE):
		result = app->runCommand("fullwrite", arg1, arg2, expect_v);
		break;
	case static_cast<int>(Command::FULLREAD):
		result = app->runCommand("fullread", arg1, arg2, expect_v);
		break;
	case static_cast<int>(Command::TESTAPP1):
		result = app->runCommand("testapp1", arg1, arg2, expect_v);
		break;
	case static_cast<int>(Command::TESTAPP2):
		result = app->runCommand("testapp2", arg1, arg2, expect_v);
		break;
	case static_cast<int>(Command::ERASE):
		result = app->runCommand("erase", arg1, arg2, expect_v);
		break;
	case static_cast<int>(Command::ERASE_RANGE):
		result = app->runCommand("erase_range", arg1, arg2, expect_v);
		break;
	case static_cast<int>(Command::FLUSH):
		result = app->runCommand("flush", arg1, arg2, expect_v);
		break;
	case static_cast<int>(Command::INVALID_COMMAND):
		cout << "INVALID COMMAND" << endl;
		break;
	case static_cast<int>(Command::INVALID_ARGUMENT):
		cout << "INVALID ARGUMENT" << endl;
		break;
	}

	return result;
}

int HostInterface::checkCmd(string input, string& arg1, string& arg2) {

	vector<string> result = split(input);

	if (result.size() < INPUT_COMMAND) {
		cout << "Empty Command" << endl;
		return static_cast<int>(Command::INVALID_COMMAND);
	}

	string cmd = result[0];

	if (cmd == "write") {
		if (result.size() < INPUT_COMMAND_ARG1_ARG2) {
			return static_cast<int>(Command::INVALID_ARGUMENT);
		}
			
		arg1 = result[1];
		if (isValidLBA(arg1) == false) {
			return static_cast<int>(Command::INVALID_ARGUMENT);
		}

		arg2 = result[2];
		if (isValidData(arg2) == false) {
			return static_cast<int>(Command::INVALID_ARGUMENT);
		}

		return static_cast<int>(Command::WRITE);
	}

	if (cmd == "read") {
		if (result.size() < INPUT_COMMAND_ARG1) {
			return static_cast<int>(Command::INVALID_ARGUMENT);
		}

		arg1 = result[1];
		if(isValidLBA(arg1) == false) {
			return static_cast<int>(Command::INVALID_ARGUMENT);
		}

		return static_cast<int>(Command::READ);
	}
	if (cmd == "exit") {
		return static_cast<int>(Command::EXIT);
	}
		
	if (cmd == "help") {
		return static_cast<int>(Command::HELP);
	}

	if (cmd == "fullwrite") {

		if (result.size() < INPUT_COMMAND_ARG1) {
			return static_cast<int>(Command::INVALID_ARGUMENT);
		}

		arg1 = result[1];
		if (isValidData(arg1) == false) {
			return static_cast<int>(Command::INVALID_ARGUMENT);
		}

		return static_cast<int>(Command::FULLWRITE);
	}

	if (cmd == "fullread") {
		return static_cast<int>(Command::FULLREAD);
	}

	if (cmd == "testapp1") {
		return static_cast<int>(Command::TESTAPP1);
	}

	if (cmd == "testapp2") {
		return static_cast<int>(Command::TESTAPP2);
	}

	if (cmd == "erase") {

		if (result.size() < INPUT_COMMAND_ARG1_ARG2) {
			return static_cast<int>(Command::INVALID_ARGUMENT);
		}

		arg1 = result[1];
		if (isValidLBA(arg1) == false) {
			return static_cast<int>(Command::INVALID_ARGUMENT);
		}

		arg2 = result[2];
		if (isValidSize(arg2) == false) {
			return static_cast<int>(Command::INVALID_ARGUMENT);
		}

		return static_cast<int>(Command::ERASE);
	}

	if (cmd == "erase_range") {

		if (result.size() < INPUT_COMMAND_ARG1_ARG2) {
			return static_cast<int>(Command::INVALID_ARGUMENT);
		}

		arg1 = result[1];
		arg2 = result[2];
		if (isValidRange(arg1, arg2) == false) {
			return static_cast<int>(Command::INVALID_ARGUMENT);
		}

		return static_cast<int>(Command::ERASE_RANGE);
	}

	if (cmd == "flush") {
		return static_cast<int>(Command::FLUSH);
	}

	if (cmd == "run_list.lst") {
		return static_cast<int>(Command::RUNNER);
	}

	if (cmd == "scenario_test") {
		return static_cast<int>(Command::SCENARIO);
	}

	return static_cast<int>(Command::INVALID_COMMAND);
}

vector<string> HostInterface::split(string input) {
	istringstream iss(input);
	string buffer;
	vector<string> result;
	char delimiter = ' ';

	int num = 0;

	while (getline(iss, buffer, delimiter) && num < 3) {
		result.push_back(buffer);
		num++;
	}

	return result;
}

bool HostInterface::isValidLBA(string arg) {

	if ((atoi(arg.c_str()) == 0) && (arg.compare("0") != 0)) {
		cout << "LBA should be decimal number" << endl;
		return false;
	}

	int num = atoi(arg.c_str());
	if (num < MIN_LBA || num > MAX_LBA) {
		cout << "LBA should be between 0 ~ 99" << endl;
		return false;
	}
		
	return true;
}

bool HostInterface::is_xdigits(const std::string& str)
{
	return str.find_first_not_of("0123456789ABCDEF") == string::npos;
}

bool HostInterface::isValidData(string arg) {
	
	string prefix = "0x";
	if (arg.rfind(prefix, 0) != 0) {
		cout << "Data should start with 0x" << endl;
		return false;
	}

	if (arg.size() != 10) {
		cout << "Data should include 10 charaters" << endl;
		return false;
	}

	arg.erase(0, 2);
	if (is_xdigits(arg) == false) {
		cout << "Data should have only A~F, 0~9" << endl;
		return false;
	}

	return true;
}

bool HostInterface::isValidSize(string arg) {

	if ((atoi(arg.c_str()) == 0) && (arg.compare("0") != 0)) {
		cout << "LBA should be decimal number" << endl;
		return false;
	}

	return true;
}

bool HostInterface::isValidRange(string arg1, string arg2) {

	if ((atoi(arg1.c_str()) == 0) && (arg1.compare("0") != 0)) {
		cout << "LBA should be decimal number" << endl;
		return false;
	}

	if ((atoi(arg2.c_str()) == 0) && (arg2.compare("0") != 0)) {
		cout << "LBA should be decimal number" << endl;
		return false;
	}

	int startLBA = atoi(arg1.c_str());
	if (startLBA < MIN_LBA || startLBA > MAX_LBA) {
		cout << "Start LBA should be between 0 ~ 99" << endl;
		return false;
	}

	int endLBA = atoi(arg2.c_str()) - 1;
	if (endLBA < MIN_LBA || endLBA > MAX_LBA) {
		cout << "End LBA should be between 1 ~ 100" << endl;
		return false;
	}

	if ( endLBA < startLBA) {
		cout << "End LBA should be bigger than StartLBA" << endl;
		return false;
	}

	return true;
}