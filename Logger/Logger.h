#pragma once

#include <fstream>
#include <filesystem>
#include <string>

using namespace std;

class Logger {
public:
	static Logger& getInstance();
	void print(const string& funcName, const string& content);
private:
	static const string LOG_PATH;
	static const string LATEST_LOG_FILE_NAME;
	
	Logger();
	Logger& operator=(const Logger& other) = delete;
	Logger(const Logger& other) = delete;

	string createUntilLogFileName(void);
	bool checkFileOpen(std::fstream& file);
	void writeToLatestLog(const string& funcName, const string& content, fstream& file);
	bool isExceedMaxFileSize(std::fstream& file);

	static const int MAX_FILE_SIZE = 10 * 1024;

	static string findUntilLogFileNameInDirectory();
	static string getFileNameWithoutExt(const string& filePath);
	static void renameLogFileToZip(const string& oldName, const string& newName);
};