#include "SSDDriver.h"

SSDDriver::SSDDriver(const string& ssdPath)
	: ssdPath_{ ssdPath } {}

void SSDDriver::write(string lba, string data) {
	
}

void SSDDriver::read(string lba) const {
	string cmd("R");
	string ret = ssdPath_ + " " + cmd + " " + lba;
	system(ret.c_str());
}