#pragma once
#include "Command.h"
#include "NandInterface.h"

class ReadCmd : public Command {
public:
	ReadCmd(int addr, NANDInterface* nand) : address(addr), nandIntf(nand) {
	}
	void run() override {
		nandIntf->read(address);
	}

private:
	int address;
	NANDInterface* nandIntf;
};