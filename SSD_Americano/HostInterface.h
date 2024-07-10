#pragma once
#include <iostream>
#include <string>
#include "NandInterface.h"

using namespace std;

class HostInterface {
public:
	HostInterface(NANDInterface* nand) : nandIntf(nand) { }

	bool checkInvalidCommand(int argc, char* argv[]);
	void processCommand(int argc, char* argv[]);
	int getCmd();
	int getAddr();
	string getData();

private:
	NANDInterface* nandIntf;
	int command = 0;
	int addr = 0;
	string data;

	const int MIN_VALID_ARGUMENT_NUM = 3;
	const int VALID_READ_ARGUMENT_NUM = 3;
	const int VALID_WRITE_ARGUMENT_NUM = 4;
	const int VALID_ERASE_ARGUMENT_NUM = 4;
	const int MIN_LBA = 0;
	const int MAX_LBA = 99;
	const int DATA_LENGTH = 10;
	const int MAX_ERASE_SIZE = 10;
};