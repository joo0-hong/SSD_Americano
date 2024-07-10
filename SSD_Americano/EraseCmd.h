#pragma once
#include "Command.h"
#include "NandInterface.h"

class EraseCmd : public Command {
public:
	EraseCmd(char* argv[], NANDInterface* nand)
		: address(atoi(argv[2])), size(string(argv[3])), nandIntf(nand) {
	}
	void run() override {
		nandIntf->erase(address, size);
	}
private:
	int address;
	string size;
	NANDInterface* nandIntf;
};