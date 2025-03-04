#pragma once

#include <string>

using std::string;

class SSDDriver {
public:
	SSDDriver(const string& ssdPath);
	virtual void write(const string& lba, const string& data) const;
	virtual void read(const string& lba) const;
	virtual void erase(const string& lba, const string& size) const;
	virtual void flush() const;

private:
	const string ssdPath_;
};