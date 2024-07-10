#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CheckCommand {
public:
	CheckCommand() {}
	int checkCmd(string input, string& arg1, string& arg2);

private:
	const int INVALID_COMMAND = -1;
	const int INVALID_ARGUMENT = -2;

	vector<string> split(string input);	

	bool isValidLBA(string arg);
	bool is_xdigits(const std::string& str);
	bool isValidData(string arg);
};
