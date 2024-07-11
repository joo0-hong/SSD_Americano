#include "ScenarioParser.h"

#include <iostream>
#include <fstream>

#include "TestShell.h"

using namespace std;



ScenarioParser& ScenarioParser::getInstance() {
	static ScenarioParser sp;
	return sp;
}

vector<ScenarioResult> ScenarioParser::test() {
	vector<ScenarioResult> result;

	rapidjson::Document document;

	if (setDocument(document) == false) {
		return vector<ScenarioResult>();
	}

	if (checkDocument(document) == false) {
		return vector<ScenarioResult>();
	}

	auto scenarios = document["scenario"].GetArray();
	for (auto& scenarioJson : scenarios) {
		ScenarioResult scenarioResult;
		vector<string> inputs;
		vector<vector<string>> expects;
		
		string scenarioName = scenarioJson["name"].GetString();
		scenarioResult.scenarioName = scenarioName;

		cout << scenarioName << endl;

		auto actions = scenarioJson["action"].GetArray();
		for (auto& actionJson : actions) {
			string actionName = actionJson["name"].GetString();
			cout << actionName << endl;

			;
			if (actionName == "fullwrite") {
				string input = getFullwriteInputString(actionJson);
				inputs.push_back(input);
				expects.push_back(vector<string>());

				continue;
			}

			if (actionName == "fullread") {
				string input = getFullReadInputString();

				vector<string> expect;
				// fullread일 때 100개 expect data 넣기
				if (actionJson.HasMember("expect")) {
					string expectData = actionJson["expect"].GetString();
					for (int i = 0; i < 100; ++i) {
						expect.push_back(expectData);
					}
				}
				
				inputs.push_back(input);
				expects.push_back(expect);
				
				continue;
			}

			int start = 0, end = 1;
			getRangeOf(actionJson, start, end);

			int lba_start = 0, lba_end = 0;
			getLBARangeOf(actionJson, lba_start, lba_end);

			cout << start << " " << end << " " << lba_start << " " << lba_end << endl;

			for (; start < end; ++start) {
				for (int l_start = lba_start; l_start < lba_end; ++l_start) {
					if (actionName == "write") {
						string input = getWriteInputString(actionJson, l_start);
						
						inputs.push_back(input);
						expects.push_back(vector<string>());
					}
					else if (actionName == "read") {
						vector<string> expect;
						string input = getReadInputString(actionJson, l_start);
						if (actionJson.HasMember("expect")) {
							expect.push_back(actionJson["expect"].GetString());
						}
						inputs.push_back(input);
						expects.push_back(expect);
					}
				}
			}
		}

		scenarioResult.inputs = inputs;
		scenarioResult.expects = expects;
		result.push_back(scenarioResult);
	}

	return result;
}

void ScenarioParser::getLBARangeOf(rapidjson::Value& actionJson, int& lba_start, int& lba_end)
{
	if (actionJson.HasMember("lba")) {
		lba_start = actionJson["lba"].GetInt();
		lba_end = lba_start + 1;
	}
	else if (actionJson.HasMember("lba_ranges")) {
		auto& lbaRangesJson = actionJson["lba_ranges"];
		lba_start = lbaRangesJson["start"].GetInt();
		lba_end = lbaRangesJson["end"].GetInt();
	}
}

void ScenarioParser::getRangeOf(rapidjson::Value& actionJson, int& start, int& end)
{
	if (actionJson.HasMember("rotate_ranges")) {
		auto& rotateJson = actionJson["rotate_ranges"];
		start = rotateJson["start"].GetInt();
		end = rotateJson["end"].GetInt();
	}
}

bool ScenarioParser::checkDocument(rapidjson::Document& document)
{
	return document.HasMember("scenario")
		&& document["scenario"].IsArray();
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

