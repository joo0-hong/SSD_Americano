#include <fstream>
#include "HostInterface.h"
#include "TestShell.h"
#include "FileReader.h"
#include "SSDDriver.h"
#include "ScenarioParser.h"

using namespace std;

int main() {
	const std::string SSD_PATH = "SSD_Americano";
	const std::string RESULT_PATH = "..\\..\\resources\\result.txt";
	const std::string RUNLIST_PATH = "..\\..\\resources\\run_list.lst";

	SSDDriver ssdDriver{ SSD_PATH };
	FileReader fileReaderMk{ RESULT_PATH };
	
	TestShell * shell = new TestShell(&ssdDriver, &fileReaderMk);
	HostInterface * hostIntf = new HostInterface(shell);

	string input;
	char delimeter = '\n';

	int scenario = static_cast<int>(Test::TEST_COMMAND);
	bool runnig = true;
	while (runnig) {
		getline(cin, input, delimeter);

		scenario = hostIntf->checkTestType(input);
		if (scenario == static_cast<int>(Test::TEST_RUNNER)) {
			ifstream ifs;
			ifs.open(RUNLIST_PATH);
			if (ifs.fail()) {
				cout << "No file" << endl;
			}
			runnig = hostIntf->processRunner(ifs);
			ifs.close();
		}
		else if (scenario == static_cast<int>(Test::TEST_SCENARIO)) {
			ScenarioParser& scenario = ScenarioParser::getInstance();
			runnig = hostIntf->processScenario(scenario);
		}
		else {
			runnig = hostIntf->processCommand(input);
		}
	}
}
