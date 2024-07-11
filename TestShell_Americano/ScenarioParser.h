#pragma once

#include <string>
#include <vector>

#include <rapidjson/document.h>

struct ScenarioResult {
	std::string scenarioName;
	std::vector<std::string> inputs;
	std::vector<std::vector<std::string>> expects;
};

class ScenarioParser
{
public:
	static ScenarioParser& getInstance();
	std::vector<ScenarioResult> test();
	void getLBARangeOf(rapidjson::Value& actionJson, int& lba_start, int& lba_end);
	void getRangeOf(rapidjson::Value& actionJson, int& start, int& end);
private:
	const std::string TEST_SCENARIO_PATH = "..\\resources\\test_scenario.json";

	ScenarioParser() = default;
	ScenarioParser(const ScenarioParser&) = delete;
	ScenarioParser& operator=(const ScenarioParser&) = delete;
	
	bool setDocument(rapidjson::Document& d);

	bool checkValid(std::ifstream& file);
	bool checkDocument(rapidjson::Document& document);
	
	std::string getWriteInputString(rapidjson::Value& actionJson, int lba);
	std::string getReadInputString(rapidjson::Value& actionJson, int lba);
	std::string getFullwriteInputString(rapidjson::Value& actionJson);
	std::string getFullReadInputString();

	std::string getStr(std::ifstream& file);
	
	void printParsingErrorMsg();
};