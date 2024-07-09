#include "SSDDriver.h"

SSDDriver::SSDDriver(const string& ssdPath)
	: ssdPath_{ ssdPath } {}

void SSDDriver::write(const string&, const string& data) const {
	
}

void SSDDriver::read(const string& lba) const {
	string cmd("R");
	string ret = ssdPath_ + " " + cmd + " " + lba;
	system(ret.c_str());
}