#include "ScenarioParser.h"

#include <iostream>
#include <fstream>

#include "TestShell.h"

using namespace std;

ScenarioParser& ScenarioParser::getInstance() {
	static ScenarioParser sp;
	return sp;
}

pair<vector<string>, vector<string>> ScenarioParser::test() {
	vector<string> inputs;
	vector<string> expects;

	rapidjson::Document document;

	if (setDocument(document) == false) {
		return make_pair(inputs, expects);
	}

	if (document.HasMember("scenario") == false
		|| document["scenario"].IsArray() == false) {
		return make_pair(inputs, expects);
	}

	auto scenarios = document["scenario"].GetArray();
	for (auto& scenarioJson : scenarios) {
		string scenarioName = scenarioJson["name"].GetString();
		cout << scenarioName << endl;

		auto actions = scenarioJson["action"].GetArray();
		for (auto& actionJson : actions) {
			string actionName = actionJson["name"].GetString();
			cout << actionName << endl;

			string input = "", expect = "";
			if (actionName == "fullwrite") {
				input = getFullwriteInputString(actionJson);
				inputs.push_back(input);

				continue;
			}
			if (actionName == "fullread") {
				input = getFullReadInputString();
				cout << "input: " << input << endl;
				inputs.push_back(input);

				// fullread일 때 100개 expect data 넣기
				if (actionJson.HasMember("expect")) {
					auto& expectJson = actionJson["expect"];
					if (expectJson.IsArray()) {}
					else {
						for (int i = 0; i < 100; ++i) {
							expects.push_back(expectJson.GetString());
						}
					}
				}
				continue;
			}


			int start = 0, end = 1;
			if (actionJson.HasMember("rotate_ranges")) {
				auto& rotateJson = actionJson["rotate_ranges"];
				start = rotateJson["start"].GetInt();
				end = rotateJson["end"].GetInt();
			}

			int lba_start = 0, lba_end = 0;
			if (actionJson.HasMember("lba")) {
				lba_start = actionJson["lba"].GetInt();
				lba_end = lba_start + 1;
			}
			else if (actionJson.HasMember("lba_ranges")) {
				auto& lbaRangesJson = actionJson["lba_ranges"];
				lba_start = lbaRangesJson["start"].GetInt();
				lba_end = lbaRangesJson["end"].GetInt();
			}

			cout << start << " " << end << " " << lba_start << " " << lba_end << endl;

			for (; start < end; ++start) {
				for (int l_start = lba_start; l_start < lba_end; ++l_start) {
					if (actionName == "write") {
						input = getWriteInputString(actionJson, l_start);
					}
					else if (actionName == "read") {
						input = getReadInputString(actionJson, l_start);
						if (actionJson.HasMember("expect")) {
							auto& expectJson = actionJson["expect"];
							if (expectJson.IsArray()) {}
							else {
								expects.push_back(expectJson.GetString());
							}
						}
					}
					inputs.push_back(input);
				}
			}
		}
	}

	return make_pair(inputs, expects);
}

string ScenarioParser::getWriteInputString(rapidjson::Value& actionJson, int lba) {
	string result = "write " + to_string(lba) + " ";

	if (actionJson.HasMember("data") == false) {
		return result;
	}

	string actionData = actionJson["data"].GetString();
	cout << actionData << endl;

	result += actionData;

	cout << result << endl;

	return result;
}
string ScenarioParser::getReadInputString(rapidjson::Value& actionJson, int lba) {
	string result = "read " + to_string(lba);
	cout << "result: " << result << endl;

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
string ScenarioParser::getFullReadInputString() {
	return "fullread";
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

