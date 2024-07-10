#pragma once
#include "Command.h"
#include "NandInterface.h"
#include <string>

using namespace std;

class WriteCmd : public Command {
public:
	WriteCmd(int addr, string data, NANDInterface* nand) : address(addr), data(data), nandIntf(nand) {
	}
	void run() override {
		nandIntf->write(address, data);
	}
private:
	int address;
	string data;
	NANDInterface* nandIntf;
};