#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include "TestShell.h"

using namespace std;

int checkCmd(vector<string> result) {
	string cmd;

	if (result.size() == 0) {
		cout << "size = " << result.size() <<  "return 0xff" << endl;
		return 0xff;
	}

	cmd = result[0];

	if (cmd == "read") {
		if (result.size() < 2) {
			cout << "cmd = " << cmd << "size = " << result.size() << "return 0xff" << endl;
			return 0xff;
		}

		return 0;
	}
	else if (cmd == "write") {
		cout << "1" << endl;
		if (result.size() < 3) {
			cout << "cmd = " << cmd << "size = " << result.size() << "return 0xff" << endl;
			return 0xff;
		}
		return 1;
	}
	else if (cmd == "exit") {
		return 2;
	}
	else if (cmd == "help") {
		return 3;
	}
	else if (cmd == "fullread") {
		return 4;
	}
	else if (cmd == "fullwrite") {
		return 5;
	}
	else {
		return -1;
	}
}


vector<string> split(string str, char Delimiter) {
	istringstream iss(str);
	string buffer;
	vector<string> result;

	while (getline(iss, buffer, Delimiter)) {
		result.push_back(buffer);
	}

	return result;
}

int main() {
	string cmd, data, LBA;
	int parsedCmd;
	string input;
	string ret = "..\\x64\\Debug\\SSDMock ";
	TestShell ts;

	system("cd");
	//fs::path current_path = fs::current_path();
	char delim = '\n';
	char split_char = ':';

	while (true) {

		getline(cin, input, delim);
		vector<string> result = split(input, ' ');

		parsedCmd = checkCmd(result);

		switch(parsedCmd) {
		case 0 :
			cmd = result[0];
			LBA = result[1];
			ret += cmd;
			ret += LBA;
			//ts.read(LBA);
			break;
		case 1:
			cmd = result[0];
			LBA = result[1];
			data = result[2];

			ret += cmd;
			ret += LBA;
			ret += data;

			//	ts.write(LBA, data);
			break;
		case 2:
			cout << "exit" << endl;
			exit(-1);
			break;
		case 3:
			cout << "help" << endl;
			break;
		case 4:
			cout << "fullread" << endl;
			break;
		case 5:
			cout << "fullwrite" << endl;
			break;

		case -1:
			cout << "INVALID COMMAND" << endl;
			break;
		default:
			cout << "INVALID ARG" << endl;
			break;
		}
	}

}