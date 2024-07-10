#include <iostream>
#include <ctime>
#include <filesystem>
#include <vector>
#include "Logger.h"

Logger& Logger::getInstance() {
	static Logger instance;
	return instance;
}
void Logger::print(const string& funcName, const string& content) {
	string filepath = "..\\..\\resources\\log\\";
	string currentFileName = "latest.log";
	string currentFileFullPath = filepath + currentFileName;

	cout << "current file name : " << currentFileFullPath << endl;

	fstream file(currentFileFullPath, ios::in | ios::out | ios::app);
	if (CheckFileOpen(file) == false) {
		return;
	}

	if (isExceedMaxFileSize(file)) {
		file.close();

		// if there is any until file, rename to zip
		string path = filepath + "*.log";
		for (const auto& file : std::filesystem::directory_iterator(path)) {
			cout << file.path() << "Needs to be renamed to ZIP" << endl;
		}

		// Create new until file
		string newFileFullPath = filepath + GetUntilFileName();
		int res = rename(currentFileFullPath.c_str(), newFileFullPath.c_str());
		cout << "RENAMING result = " << res << endl;

		// re-open file
		file.open(currentFileName, ios::in | ios::out | ios::app);
	}

	WriteToLatestLog(funcName, content, file);

	file.close();
}

bool Logger::isExceedMaxFileSize(std::fstream& file)
{
	file.seekg(0, ios_base::end);
	cout << "file size = " << file.tellg() << " Bytes" << endl;
	return file.tellg() >= Logger::MAX_FILE_SIZE;
}

void Logger::WriteToLatestLog(const string& funcName, const string& content, fstream& file)
{
	time_t timer = time(NULL);
	tm time;
	localtime_s(&time, &timer);

	string logTime = to_string(time.tm_year - 100)
		+ string(".")
		+ to_string(time.tm_mon)
		+ string(".")
		+ to_string(time.tm_mday)
		+ string(" ")
		+ to_string(time.tm_hour)
		+ string(":")
		+ to_string(time.tm_min);

	file << format("[{0: <13}] {1: <20} : {2: <20}\n", logTime, funcName, content);
}

string Logger::GetUntilFileName()
{
	time_t timer = time(NULL);
	tm time;

	localtime_s(&time, &timer);
	// example : until_240710_11h_46m_50s.log
	return "until"
		+ string("_")
		+ to_string(time.tm_year - 100)
		+ to_string(time.tm_mon)
		+ to_string(time.tm_wday)
		+ string("_")
		+ to_string(time.tm_hour)
		+ string("h_")
		+ to_string(time.tm_min)
		+ string("m_")
		+ to_string(time.tm_sec)
		+ string("s")
		+ ".log";
}

bool Logger::CheckFileOpen(std::fstream& file)
{
	if (false == file.is_open()) {
		cout << "FILE should be opened " << endl;
		return false;
	}
	cout << "FILE is opened" << endl;
	return true;
}