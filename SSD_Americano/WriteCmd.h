#pragma once
#include "Command.h"
#include "NandInterface.h"

class WriteCmd : public Command {
public:
	WriteCmd(char* argv[], NANDInterface* nand) 
		: address(atoi(argv[2])), data(string(argv[3])), nandIntf(nand) {
	}
	void run() override {
		nandIntf->write(address, data);
	}
private:
	int address;
	string data;
	NANDInterface* nandIntf;
};