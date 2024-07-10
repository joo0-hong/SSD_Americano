#include "SSDDriver.h"

SSDDriver::SSDDriver(const string& ssdPath)
	: ssdPath_{ ssdPath } {}

void SSDDriver::write(const string& lba, const string& data) const {
	string cmd("W");
	string ret = ssdPath_ + " " + cmd + " " + lba + " " + data;
	system(ret.c_str());
}

void SSDDriver::read(const string& lba) const {
	string cmd("R");
	string ret = ssdPath_ + " " + cmd + " " + lba;
	system(ret.c_str());
}

void SSDDriver::erase(const string& lba, const string& size) const {
	string cmd("E");
	string ret = ssdPath_ + " " + cmd + " " + lba + " " + size;
	system(ret.c_str());
}