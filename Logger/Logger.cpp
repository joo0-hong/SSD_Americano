#include <iostream>
#include <ctime>
#include <experimental/filesystem>
#include <vector>
#include "Logger.h"

void Logger::print(const string& funcName, const string& content) {
	string filepath = "../resources/";
	string currentFileName = "latest.log";
	string currentFileFullPath = filepath + currentFileName;

	// open file with app option (append)
	fstream file(currentFileName, ios::in | ios::out | ios::app);

	// check file open
	if (CheckFileOpen(file) == false) {
		return;
	}

	// Check size and renaming
	if (file.tellg() >= Logger::MAX_FILE_SIZE) {
		file.close();

		// if there is any until file, rename to zip
		string path = filepath + "*.log";
		for (const auto& file : std::experimental::filesystem::directory_iterator(path)) {
			cout << file.path() << "Needs to be renamed to ZIP" << endl;
		}

		// Create new until file
		string newFileFullPath = filepath + GetUntilFileName();
		int res = rename(currentFileFullPath.c_str(), newFileFullPath.c_str());
		cout << "RENAMING result = " << res << endl;

		// re-open file
		file.open(currentFileName, ios::in | ios::out | ios::app);
	}

	// Write to file
	string str = funcName + " :: " + content;
	file << str;

	// close file
	file.close();
}

string Logger::GetUntilFileName()
{
	time_t timer = time(NULL);
	tm time;

	localtime_s(&time, &timer);
	//until_240710_11h_46m_50s.log)
	return "until"
		+ to_string(time.tm_year)
		+ to_string(time.tm_mon)
		+ to_string(time.tm_wday);
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