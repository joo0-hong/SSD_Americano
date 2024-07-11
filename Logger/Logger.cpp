#include <iostream>
#include <ctime>
#include <filesystem>
#include <vector>

#include "Logger.h"

using namespace std::filesystem;

const string Logger::LOG_PATH = "..\\..\\resources\\log\\";
const string Logger::LATEST_LOG_FILE_NAME = "latest.log";
const int Logger::MAX_FILE_SIZE = 10 * 1024;

Logger::Logger() {}

Logger& Logger::getInstance() {
	static Logger instance;
	return instance;
}
void Logger::print(const string& funcName, const string& content) {
	string currentFileFullPath = LOG_PATH + LATEST_LOG_FILE_NAME;

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
			renameLogToZIPFile(untilLogFileName);
		}

		createNewUntilLogFile();

		// re-open file
		createLatestLogFile(file, currentFileFullPath);
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
	return true;
}
bool Logger::isExceedMaxFileSize(std::fstream& file)
{
	file.seekg(0, ios_base::end);
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

void Logger::renameLogToZIPFile(const std::string& untilLogFileName)
{
	cout << untilLogFileName << " Needs to be renamed to ZIP" << endl;

	string oldName = LOG_PATH + untilLogFileName;
	string newName = LOG_PATH + getFileNameWithoutExt(untilLogFileName) + ".zip";

	renameWithString(oldName, newName);
}

void Logger::renameWithString(const string& oldName, const string& newName)
{
	int ret = rename(oldName.c_str(), newName.c_str());

	if (ret != 0) {
		cout << "Logger Error Code: " << ret << endl;
	}
}

void Logger::createNewUntilLogFile()
{
	string oldName = LOG_PATH + LATEST_LOG_FILE_NAME;
	string newName = LOG_PATH + createUntilLogFileName();

	renameWithString(oldName, newName);
}

string Logger::createUntilLogFileName()
{
	time_t timer = time(NULL);
	tm time;

	localtime_s(&time, &timer);

	// example : until_240710_11h_46m_50s.log
	return format("until_{}{:0>2}{:0>2}_{:0>2}h_{:0>2}m_{:0>2}s.log"
		, (time.tm_year - 100), time.tm_mon + 1, time.tm_mday, time.tm_hour, time.tm_min, time.tm_sec);
}

void Logger::createLatestLogFile(std::fstream& file, std::string& currentFileFullPath)
{
	file.open(currentFileFullPath, ios::in | ios::out | ios::app);
}

void Logger::writeToLatestLog(const string& funcName, const string& content, fstream& file)
{
	time_t timer = time(NULL);
	tm time;
	localtime_s(&time, &timer);

	string timeStr = format("{}.{:0>2}.{:0>2} {:0>2}:{:0>2}"
		, (time.tm_year - 100), time.tm_mon + 1, time.tm_mday, time.tm_hour, time.tm_min);

	file << format("[{0: <14}] {1: <40} : {2: <30}\n", timeStr, funcName, content);
}