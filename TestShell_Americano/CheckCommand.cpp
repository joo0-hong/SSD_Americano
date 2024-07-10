#include "CheckCommand.h"

int CheckCommand::checkCmd(string input, string& arg1, string& arg2) {

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

	return static_cast<int>(Command::INVALID_COMMAND);
}

vector<string> CheckCommand::split(string input) {
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

bool CheckCommand::isValidLBA(string arg) {

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

bool CheckCommand::is_xdigits(const std::string& str)
{
	return str.find_first_not_of("0123456789ABCDEF") == string::npos;
}

bool CheckCommand::isValidData(string arg) {
	
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

bool CheckCommand::isValidSize(string arg) {

	if ((atoi(arg.c_str()) == 0) && (arg.compare("0") != 0)) {
		cout << "LBA should be decimal number" << endl;
		return false;
	}
}

bool CheckCommand::isValidRange(string arg1, string arg2) {

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