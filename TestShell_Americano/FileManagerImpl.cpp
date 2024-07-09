#include <fstream>

#include "FileManagerImpl.h"

using std::ifstream;

FileManagerImpl::FileManagerImpl(const string& filePath) {
	filePath_ = filePath;
}

string FileManagerImpl::readFile()
{
	string result;

	ifstream ifs;
	ifs.open(filePath_);
	ifs >> result;
	ifs.close();

	return result;
}
