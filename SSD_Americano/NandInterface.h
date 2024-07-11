#pragma once
#include <string>

using namespace std;
#define interface struct

interface NANDInterface {
public:
	virtual void read(int lba) = 0;
	virtual void write(int lba, string data) = 0;
	virtual void erase(int lba, int size) = 0;
	virtual void flush(void) = 0;
	virtual void error(void) = 0;
	virtual void writeResult(string result) = 0;
};
