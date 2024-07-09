#pragma once

#include <string>

using std::string;

class SSDDriver {
public:
	SSDDriver(const string& ssdPath);
	virtual void write(string lba, string data);
	virtual void read(string lba) const;

private:
	const string ssdPath_;
};