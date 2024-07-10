#include <iostream>
#include <ctime>
#include <filesystem>
#include <vector>

#include "Logger.h"

using namespace std::filesystem;

const string Logger::LOG_PATH = "..\\resources\\log\\";
const string Logger::LATEST_LOG_FILE_NAME = "latest.log";

void Logger::print(const string& funcName, const string& content) {
	string currentFileFullPath = LOG_PATH + LATEST_LOG_FILE_NAME;

	// open file with app option (append)
	fstream file(currentFileFullPath, ios::in | ios::out | ios::app);

	// check file open
	if (CheckFileOpen(file) == false) {
		return;
	}

	int sz = 0;
	file.seekg(0, ios_base::end);
	cout << "tellg(): " << file.tellg() << endl;
	sz = file.tellg();

	// Check size and renaming
	if (sz >= Logger::MAX_FILE_SIZE) {
		file.close();

		// if there is any until file, rename to zip
		string fileName = getUntilLogFileName();
		cout << fileName << " Needs to be renamed to ZIP" << endl;
		
		string fileNameWithoutExt = getFileNameWithoutExt(fileName);

		renameLogFileToZip(fileNameWithoutExt);

		//// Create new until file
		//string newFileFullPath = LOG_PATH + GetUntilFileName();
		//int res = rename(currentFileFullPath.c_str(), newFileFullPath.c_str());
		//cout << "RENAMING result = " << res << endl;

		// re-open file
		file.open(LATEST_LOG_FILE_NAME, ios::in | ios::out | ios::app);
	}

	// Write to file
	string str = funcName + " :: " + content;
	file << str;

	// close file
	file.close();
}

string Logger::getUntilLogFileName()
{
	string result = "";
	for (const auto& file : directory_iterator(LOG_PATH)) {
		result = file.path().filename().u8string();
		string fname = result;
		
		if (fname == LATEST_LOG_FILE_NAME) {
			continue;
		}

		// only until_xxx.log file can pass
		const std::string delimiter = ".";
		size_t pos = fname.find(delimiter);
		fname.erase(0, pos + delimiter.length());

		if (fname == "log") {
			break;
		}

	}

	return result;
}
string Logger::getFileNameWithoutExt(const string& fname)
{
	return fname.substr(0, fname.find("."));
}
void Logger::renameLogFileToZip(const string& fname)
{
	string oldName = LOG_PATH + fname + ".log";
	string newName = LOG_PATH + fname + ".zip";

	int ret = rename(oldName.c_str(), newName.c_str());

	cout << "complete rename - " << ret << endl;

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