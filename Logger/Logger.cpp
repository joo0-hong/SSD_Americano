#include <iostream>
#include <ctime>
#include <filesystem>
#include <vector>

#include "Logger.h"

using namespace std::filesystem;

const string Logger::LOG_PATH = "..\\resources\\log\\";
const string Logger::LATEST_LOG_FILE_NAME = "latest.log";

Logger::Logger() {}

Logger& Logger::getInstance() {
	static Logger instance;
	return instance;
}
void Logger::print(const string& funcName, const string& content) {
	string currentFileFullPath = LOG_PATH + LATEST_LOG_FILE_NAME;

	cout << "current file name : " << currentFileFullPath << endl;

	// open file with app option (append)
	fstream file(currentFileFullPath, ios::in | ios::out | ios::app);

	if (checkFileOpen(file) == false) {
		return;
	}

	if (isExceedMaxFileSize(file)) {
		file.close();

		// if there is some until_file, rename to zip
		string untilLogFileName = findUntilLogFileNameInDirectory();
		
		if (untilLogFileName != "") {
			cout << untilLogFileName << " Needs to be renamed to ZIP" << endl;
			
			string oldName = LOG_PATH + untilLogFileName;
			string newName = LOG_PATH + getFileNameWithoutExt(untilLogFileName) + ".zip";

			renameLogFileToZip(oldName, newName);
		}

		// Create new until file
		string oldName = LOG_PATH + LATEST_LOG_FILE_NAME;
		string newName = LOG_PATH + createUntilLogFileName();

		renameLogFileToZip(oldName, newName);
		//cout << "RENAMING result = " << res << endl;

		// re-open file
		file.open(currentFileFullPath, ios::in | ios::out | ios::app);
	}

	writeToLatestLog(funcName, content, file);

	file.close();
}

bool Logger::checkFileOpen(std::fstream& file)
{
	if (false == file.is_open()) {
		cout << "FILE should be opened " << endl;
		return false;
	}
	cout << "FILE is opened" << endl;
	return true;
}
bool Logger::isExceedMaxFileSize(std::fstream& file)
{
	file.seekg(0, ios_base::end);
	cout << "file size = " << file.tellg() << " Bytes" << endl;
	return file.tellg() >= Logger::MAX_FILE_SIZE;
}

string Logger::findUntilLogFileNameInDirectory()
{
	string result = "";
	for (const auto& file : directory_iterator(LOG_PATH)) {
		string fname = file.path().filename().string();
		
		if (fname == LATEST_LOG_FILE_NAME) {
			continue;
		}

		// only until_xxx.log file can pass
		const std::string delimiter = ".";
		size_t pos = fname.find(delimiter);
		fname.erase(0, pos + delimiter.length());

		if (fname == "log") {
			result = file.path().filename().string();
			break;
		}
	}

	return result;
}
string Logger::getFileNameWithoutExt(const string& fname)
{
	return fname.substr(0, fname.find("."));
}
void Logger::renameLogFileToZip(const string& oldName, const string& newName)
{
	int ret = rename(oldName.c_str(), newName.c_str());

	if (ret != 0) {
		cout << "Logger Error Code: " << ret << endl;
	}
}

string Logger::createUntilLogFileName()
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

void Logger::writeToLatestLog(const string& funcName, const string& content, fstream& file)
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