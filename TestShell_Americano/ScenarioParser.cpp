#include "ScenarioParser.h"

#include <iostream>
#include <fstream>

#include "TestShell.h"

using namespace std;

ScenarioParser& ScenarioParser::getInstance() {
	static ScenarioParser sp;
	return sp;
}

void ScenarioParser::test() {
	rapidjson::Document document;

	if (setDocument(document) == false) {
		return;
	}

	auto& scenarioJson = document["scenario"];
	auto scenarios = scenarioJson.GetArray();
	for (auto& scenarioJson : scenarios) {
		string scenarioName = scenarioJson["name"].GetString();
		cout << scenarioName << endl;

		auto actions = scenarioJson["action"].GetArray();
		for (auto& actionJson : actions) {
			string actionName = actionJson["name"].GetString();
			cout << actionName << endl;

			// actionName: write
			if (actionName == "write") {
				
			}
		}

	}
}

bool ScenarioParser::setDocument(rapidjson::Document& d) {
	ifstream file(TEST_SCENARIO_PATH);

	if (checkValid(file) == false) {
		cout << "Can't open file. Please Check file Path." << endl;

		return false;
	}

	string jsonText = getStr(file);

	rapidjson::ParseResult pr = d.Parse(jsonText.c_str());
	if (pr.IsError()) {
		printParsingErrorMsg();

		return false;
	}

	return true;
}

bool ScenarioParser::checkValid(std::ifstream& file)
{
	return file.is_open();
}

string ScenarioParser::getStr(std::ifstream& file) {
	string result = "", str;
	
	while (file >> str) {
		result += str;
	}

	return result;
}

void ScenarioParser::printParsingErrorMsg()
{
	cout << "pr.IsError()" << endl;
	cout << "This is Wrong JSON File. Please modify content." << endl;
}

