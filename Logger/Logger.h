#pragma once

#include <fstream>
#include <string>

using namespace std;

class Logger {
public:
	static Logger& getInstance();
	void print(const string& funcName, const string& content);
private:
	Logger() {

	}
	Logger& operator=(const Logger& other) = delete;
	Logger(const Logger& other) = delete;

	string GetUntilFileName(void);
	bool CheckFileOpen(std::fstream& file);
	void WriteToLatestLog(const string& funcName, const string& content, fstream& file);
	bool isExceedMaxFileSize(std::fstream& file);

	static const int MAX_FILE_SIZE = 10 * 1024;
};