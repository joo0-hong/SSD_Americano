#include "CheckCommand.h"
#include "TestShell.h"
#include "FileReader.h"
#include "SSDDriver.h"

using namespace std;

int main() {
	const std::string SSD_PATH = "SSD_Americano";
	const std::string RESULT_PATH = "..\\..\\resources\\result.txt";

	SSDDriver ssdDriver{ SSD_PATH };
	FileReader fileReaderMk{ RESULT_PATH };
	TestShell app{ &ssdDriver, &fileReaderMk };

	CheckCommand checker;

	string input;
	string arg1, arg2;
	char delimeter = '\n';

	bool ret = true;
	while (ret) {
		getline(cin, input, delimeter);
		int cmd = checker.checkCmd(input, arg1, arg2);

		switch (cmd) {
		case static_cast<int>(Command::WRITE):
			ret = app.runCommand("write", arg1, arg2);
			break;
		case static_cast<int>(Command::READ):
			ret = app.runCommand("read", arg1, arg2);
			break;
		case static_cast<int>(Command::EXIT):
			ret = app.runCommand("exit", arg1, arg2);
			break;
		case static_cast<int>(Command::HELP):
			ret = app.runCommand("help", arg1, arg2);
			break;
		case static_cast<int>(Command::FULLWRITE):
			ret = app.runCommand("fullwrite", arg1, arg2);
			break;
		case static_cast<int>(Command::FULLREAD):
			ret = app.runCommand("fullread", arg1, arg2);
			break;
		case static_cast<int>(Command::ERASE):
			ret = app.runCommand("erase", arg1, arg2);
			break;
		case static_cast<int>(Command::ERASE_RANGE):
			ret = app.runCommand("erase_range", arg1, arg2);
			break;
		case static_cast<int>(Command::FLUSH):
			ret = app.runCommand("flush", arg1, arg2);
			break;
		case static_cast<int>(Command::TESTAPP1):
			cout << "testapp1" << endl;
			app.testapp1();
			break;
		case static_cast<int>(Command::TESTAPP2):
			cout << "testapp2" << endl;
			app.testapp2();
			break;
		case static_cast<int>(Command::SCENARIO):
			break;
		case static_cast<int>(Command::INVALID_COMMAND):
			cout << "INVALID COMMAND" << endl;
			break;
		case static_cast<int>(Command::INVALID_ARGUMENT):
			cout << "INVALID ARGUMENT" << endl;
			break;
		}
	}

}
