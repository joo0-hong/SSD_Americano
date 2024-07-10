#pragma once
#include "Command.h"
#include "NandInterface.h"

class ReadCmd : public Command {
public:
	ReadCmd(char* argv[], NANDInterface* nand) 
		: address(atoi(argv[2])), nandIntf(nand) {
	}
	void run() override {
		nandIntf->read(address);
	}

private:
	int address;
	NANDInterface* nandIntf;
};