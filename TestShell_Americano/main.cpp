#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>

#include "CheckCommand.cpp"
#include "TestShell.h"
#include "FileReader.h"
#include "SSDDriver.h"

using namespace std;

int main() {
	const std::string SSD_PATH = "..\\x64\\Debug\\SSD_Americano";
	const std::string RESULT_PATH = "..\\resources\\result.txt";

	SSDDriver ssdDriver{ SSD_PATH };
	FileReader fileReaderMk{ RESULT_PATH };
	TestShell app{ &ssdDriver, &fileReaderMk };

	CheckCommand checker;

	string input;
	string arg1, arg2;
	char delimeter = '\n';

	while (true) {
		getline(cin, input, delimeter);
		int cmd = checker.checkCmd(input, arg1, arg2);

		switch (cmd) {
		case 0:
			cout << "write (" <<arg1 << ", " << arg2 << ")" << endl;
			app.write(arg1, arg2);
			break;
		case 1:
			cout << "read (" << arg1 << ")" << endl;
			app.read(arg1);
			break;
		case 2:
			cout << "exit" << endl;
			app.exit();
			break;
		case 3:
			cout << "help" << endl;
			app.help();
			break;
		case 4:
			cout << "fullwrite (" << arg1 << ")" << endl;
			app.fullwrite(arg1);
			break;
		case 5:
			cout << "fullread" << endl;
			app.fullread();
			break;
		case -1:
			cout << "INVALID COMMAND" << endl;
			break;
		default:
			cout << "INVALID ARGUMENT" << endl;
			break;
		}
	}

}
