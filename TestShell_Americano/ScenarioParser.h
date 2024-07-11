#pragma once

#include <string>

#include <rapidjson/document.h>

class ScenarioParser
{
public:
	static ScenarioParser& getInstance();
	void test();
private:
	const std::string TEST_SCENARIO_PATH = "..\\resources\\test_scenario.json";
	
	ScenarioParser() = default;
	ScenarioParser(const ScenarioParser&) = delete;
	ScenarioParser& operator=(const ScenarioParser&) = delete;
	
	bool setDocument(rapidjson::Document& d);

	bool checkValid(std::ifstream& file);
	
	std::string getStr(std::ifstream& file);
	
	void printParsingErrorMsg();
};