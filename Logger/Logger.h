#pragma once

#include <fstream>
#include <filesystem>
#include <string>

using namespace std;

class Logger {
public:
	static void print(const string& funcName, const string& content);
private:
	static string GetUntilFileName(void);
	static bool CheckFileOpen(std::fstream& file);
	static const int MAX_FILE_SIZE = 10 * 1024;

	static const string LOG_PATH;
	static const string LATEST_LOG_FILE_NAME;
	
	static string getUntilLogFileName();
	static string getFileNameWithoutExt(const string& filePath);
	static void renameLogFileToZip(const string& fname);
};