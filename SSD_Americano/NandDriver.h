#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "NANDBuffer.h"
#include "NandInterface.h"
#include "FileManager.h"

using namespace std;

class NANDDriver {
public:
	NANDDriver(NANDInterface* nand, NANDBuffer* nandBuffer) 
		: nand(nand), nandBuffer(nandBuffer)
	{};
	void read(const int lba);
	void write(const int lba, const string data);
	void erase(const int lba, const int size);
	void error(void);
	void flush(void);

private:
	NANDBuffer* nandBuffer;
	NANDInterface* nand;
	const int MAX_BUFFER_NUM = 10;
};