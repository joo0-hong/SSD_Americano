#pragma once
#include <string>

using std::string;

class FileReader
{
public:
	FileReader(const string& filePath);
	virtual string readFile();
private:
	string filePath_;
};