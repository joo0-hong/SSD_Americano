#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int checkCmd(vector<string> input) { 

	string cmd = input[0];

	if (cmd == "read") {
		if (input.size() < 2)	{
			cout << "cmd = " << cmd << " size = " << input.size() << " return 0xff" << endl;
			return 0xff;
 		}
		return 0;
	}
	else if (cmd == "write") {
		if (input.size() < 3) {
			cout << "cmd = " << cmd << " size = " << input.size() << " return 0xff" << endl;
			return 0xff;
		}
		return 1;
	}
	else if (cmd == "exit") {
		return 2;
	}
	if (cmd == "help") {
		return 3;
	}
	if (cmd == "fullread") {
		return 4;
	}
	if (cmd == "fullwrite") {
		return 5;
	}
	return -1;
}

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


int main() {
	string input;
	char delimeter = '\n';


	while (true) {

		getline(cin, input, delimeter);
		vector<string> result = split(input, ' ');

		int cmd = checkCmd(result);
		string ret = "..\\x64\\Debug\\SSDMock ";

		switch (cmd) {
		case 0:
			cout << "read" << endl;
			ret += result[0];
			ret += result[1];
			break;
		case 1:
			cout << "write" << endl;
			ret += result[0];
			ret += result[1];
			ret += result[2];
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
			cout << "INVALID ARGUMENT" << endl;
			break;
		}

	//	system(ret.c_str());
	}

}