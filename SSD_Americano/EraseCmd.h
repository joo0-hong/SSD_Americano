#pragma once
#include "Command.h"
#include "NandInterface.h"
#include <string>

using namespace std;

class EraseCmd : public Command {
public:
	EraseCmd(int addr, string size, NANDInterface* nand) : address(addr), size(size), nandIntf(nand) {
	}
	void run() override {
		nandIntf->erase(address, size);
	}
private:
	int address;
	string size;
	NANDInterface* nandIntf;
};