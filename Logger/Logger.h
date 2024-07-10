#pragma once

#include <fstream>
#include <string>

using namespace std;

class Logger {
public:
	static void print(const string& funcName, const string& content);
private:
	static string GetUntilFileName(void);
	static bool CheckFileOpen(std::fstream& file);
	static void WriteToLatestLog(const string& funcName, const string& content, fstream& file);
	static bool isExceedMaxFileSize(std::fstream& file);
	static const int MAX_FILE_SIZE = 10 * 1024;
};