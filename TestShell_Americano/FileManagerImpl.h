#pragma once

#include <string>

#include "FileManager.h"

using std::string;

class FileManagerImpl : public FileManager
{
public:
	FileManagerImpl(const string& filePath);
	string readFile() override;
private:
	string filePath_;
};

