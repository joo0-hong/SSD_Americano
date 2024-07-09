#pragma once
#include <string>

#define interface struct

using std::string;

interface FileManager
{
	virtual string readFile() = 0;
};