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
	static const int MAX_FILE_SIZE;
	
	Logger();
	Logger& operator=(const Logger& other) = delete;
	Logger(const Logger& other) = delete;

	bool checkFileOpen(std::fstream& file);
	bool isExceedMaxFileSize(std::fstream& file);

	static string findUntilLogFileNameInDirectory();
	static string getFileNameWithoutExt(const string& filePath);
	void renameLogToZIPFile(const std::string& untilLogFileName);
	static void renameWithString(const string& oldName, const string& newName);
	
	void createNewUntilLogFile();
	string createUntilLogFileName(void);

	string addZeroForTimeString(int timeVal);

	void createLatestLogFile(std::fstream& file, std::string& currentFileFullPath);

	void writeToLatestLog(const string& funcName, const string& content, fstream& file);
};