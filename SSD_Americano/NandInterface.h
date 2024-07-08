#pragma once
#include <string>

using namespace std;
#define interface struct

interface NANDInterface {
public:
	virtual void read(int lba) = 0;
	virtual void write(int lba, int data) = 0;
};