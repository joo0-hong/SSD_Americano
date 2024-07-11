#include "HostInterface.h"
#include "TestShell.h"
#include "FileReader.h"
#include "SSDDriver.h"

using namespace std;

int main() {
	const std::string SSD_PATH = "SSD_Americano";
	const std::string RESULT_PATH = "..\\..\\resources\\result.txt";

	SSDDriver ssdDriver{ SSD_PATH };
	FileReader fileReaderMk{ RESULT_PATH };
	
	TestShell * shell = new TestShell(&ssdDriver, &fileReaderMk);
	HostInterface * hostIntf = new HostInterface(shell);

	string input;
	char delimeter = '\n';

	bool runnig = true;
	while (runnig) {
		getline(cin, input, delimeter);
		runnig = hostIntf->processCommand(input);
	}
}
