#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>

using namespace std;


class CheckCommand {
public:

	int checkCmd(string input, string arg1, string arg2) {

		char delimeter = ' ';
		vector<string> result = split(input, delimeter);

		if (result.size() < 1) {
			cout << "Empty Command" << endl;
			return INVALID_COMMAND;
		}

		string cmd = result[0];

		if (cmd == "write") {
			if (result.size() < 3) {
				cout << "cmd = " << cmd << " size = " << result.size() << " return " << INVALID_ARGUMENT << endl;
				return INVALID_ARGUMENT;
			}
			
			arg1 = result[1];
			if (isValidLBA(arg1) == false) {
				cout << "cmd = " << cmd << " invalide arg" << " return " << INVALID_ARGUMENT << endl;
				return INVALID_ARGUMENT;
			}

			arg2 = result[2];
			if (isValidData(arg2) == false) {
				cout << "cmd = " << cmd << " invalide arg" << " return " << INVALID_ARGUMENT << endl;
				return INVALID_ARGUMENT;
			}

			return 0;
		}

		if (cmd == "read") {
			if (result.size() < 2) {
				cout << "cmd = " << cmd << " size = " << result.size() << " return " << INVALID_ARGUMENT << endl;
				return INVALID_ARGUMENT;
			}

			arg1 = result[1];
			if(isValidLBA(arg1) == false) {
				cout << "cmd = " << cmd << " invalide arg" << " return " << INVALID_ARGUMENT << endl;
				return INVALID_ARGUMENT;
			}

			return 1;
		}
		if (cmd == "exit") {
			return 2;
		}
		
		if (cmd == "help") {
			return 3;
		}

		if (cmd == "fullwrite") {

			if (result.size() < 2) {
				cout << "cmd = " << cmd << " size = " << result.size() << " return " << INVALID_ARGUMENT << endl;
				return INVALID_ARGUMENT;
			}

			arg1 = result[1];
			if (isValidData(arg1) == false) {
				cout << "cmd = " << cmd << " invalide arg" << " return " << INVALID_ARGUMENT << endl;
				return INVALID_ARGUMENT;
			}

			return 4;
		}

		if (cmd == "fullread") {
			return 5;
		}

		return INVALID_COMMAND;
	}

private:

	const int INVALID_COMMAND = -1;
	const int INVALID_ARGUMENT = 0xff;

	vector<string> split(string input, char delimiter) {
		istringstream iss(input);
		string buffer;
		vector<string> result;
		int num = 0;

		while (getline(iss, buffer, delimiter) && num < 3) {
			result.push_back(buffer);
			num++;
		}

		return result;
	}

	bool isValidLBA(string arg) {

		if ((atoi(arg.c_str()) == 0) && (arg.compare("0") != 0)) {
			cout << "LBA should be decimal number" << endl;
			return false;
		}

		int num = atoi(arg.c_str());
		if (num < 0 || num > 99) {
			cout << "LBA should be between 0 ~ 99" << endl;
			return false;
		}
		
		return true;
	}

	bool is_xdigits(const std::string& str)
	{
		return str.find_first_not_of("0123456789ABCDEF") == string::npos;
	}


	bool isValidData(string arg) {
	
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

		unsigned int num;
		istringstream iss(arg);
		iss >> hex >> num;

		if (num < 0x00000000 || num > 0xFFFFFFFF) {
			cout << "Data should be number (0x00000000 ~ 0xFFFFFFFF)" << endl;
			return false;
		}

		return true;
	}

};
