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
			cout << "write (" <<arg1 << ", " << arg2 << ")" << endl;
			app.write(arg1, arg2);
			break;
		case static_cast<int>(Command::READ):
			cout << "read (" << arg1 << ")" << endl;
			app.read(arg1);
			break;
		case static_cast<int>(Command::EXIT):
			cout << "exit" << endl;
			ret = app.exit();
			break;
		case static_cast<int>(Command::HELP):
			cout << "help" << endl;
			app.help();
			break;
		case static_cast<int>(Command::FULLWRITE):
			cout << "fullwrite (" << arg1 << ")" << endl;
			app.fullwrite(arg1);
			break;
		case static_cast<int>(Command::FULLREAD):
			cout << "fullread" << endl;
			app.fullread();
			break;
		case static_cast<int>(Command::ERASE):
			cout << "erase (" << arg1 << ", " << arg2 << ")" << endl;
			app.erase(arg1, arg2);
			break;
		case static_cast<int>(Command::ERASE_RANGE):
			cout << "erase_range (" << arg1 << ", " << arg2 << ")" << endl;
			app.erase_range(arg1, arg2);
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
