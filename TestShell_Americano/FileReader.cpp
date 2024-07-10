#include <fstream>

#include "FileReader.h"

using std::ifstream;

FileReader::FileReader(const string& filePath) {
	filePath_ = filePath;
}

string FileReader::readFile()
{
	string result;

	ifstream ifs;
	ifs.open(filePath_);
	ifs >> result;
	ifs.close();

	return result;
}
