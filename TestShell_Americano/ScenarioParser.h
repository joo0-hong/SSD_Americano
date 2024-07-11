#pragma once

#include <string>
#include <vector>

#include <rapidjson/document.h>

class ScenarioParser
{
public:
	static ScenarioParser& getInstance();
	std::pair<std::vector<std::string>, std::vector<std::vector<std::string>>> test();
private:
	const std::string TEST_SCENARIO_PATH = "..\\..\\resources\\test_scenario.json";
	
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