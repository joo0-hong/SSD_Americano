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

			string input = "";
			if (actionName == "write") {
				input = getWriteInputString(actionJson);
			}
			if (actionName == "fullwrite") {
				input = getFullwriteInputString(actionJson);
			}
			if (actionName == "fullread") {

			}

			// is_rotate가 true라면 현재 action을 ranges만큼 반복한다.
			if (actionJson.HasMember("rotate_ranges")) {
				auto& rotateJson = actionJson["rotate_ranges"];
				int start = rotateJson["start"].GetInt();
				int end = rotateJson["end"].GetInt();

				// processCommand를 [start : end) 만큼 실행
				for (; start < end; ++start) {
					
				}
			}

			

			// processCommand(input) 호출하면 동작.
		}

	}
}

string ScenarioParser::getWriteInputString(rapidjson::Value& actionJson) {
	string result = "write ";
	cout << "write" << endl;

	if (actionJson.HasMember("data") == false)
		return result;

	if (actionJson.HasMember("lba")) {
		string lba = to_string(actionJson["lba"].GetInt());
	}

	string actionData = actionJson["data"].GetString();
	cout << actionData << endl;

	result += actionData;

	return result;
}

string ScenarioParser::getFullwriteInputString(rapidjson::Value& actionJson)
{
	string result = "fullwrite ";
	cout << "fullwrite" << endl;

	if (actionJson.HasMember("data") == false)
		return result;

	string actionData = actionJson["data"].GetString();
	cout << actionData << endl;

	result += actionData;

	return result;
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

