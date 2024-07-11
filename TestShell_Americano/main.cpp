#include "HostInterface.h"
#include "TestShell.h"
#include "FileReader.h"
#include "SSDDriver.h"
#include "ScenarioParser.h"

using namespace std;

int main() {
	const std::string SSD_PATH = "SSD_Americano";
	const std::string RESULT_PATH = "..\\..\\resources\\result.txt";
	const std::string SCENARIO_PATH = "..\\..\\resources\\run_list.lst";

	SSDDriver ssdDriver{ SSD_PATH };
	FileReader fileReaderMk{ RESULT_PATH };
	
	TestShell * shell = new TestShell(&ssdDriver, &fileReaderMk);
	HostInterface * hostIntf = new HostInterface(shell);

	string input;
	char delimeter = '\n';

	bool scenario = true;
	bool runnig = true;
	while (runnig) {
		getline(cin, input, delimeter);
		scenario = hostIntf->checkSenarioTest(input);
		if (scenario) {
			ScenarioParser& scenario = ScenarioParser::getInstance();
			runnig = hostIntf->processScenario(scenario);
		}
		else {
			runnig = hostIntf->processCommand(input);
		}
	}
}
