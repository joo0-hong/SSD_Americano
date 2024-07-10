#pragma once

#include <string>

using std::string;

class Logger {
public:
	static void print(const string& funcName, const string& content);
};