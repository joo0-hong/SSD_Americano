#pragma once
#include "Command.h"
#include "NandInterface.h"

class ReadCmd : public Command {
public:
	ReadCmd(NANDInterface* nand) : nandIntf(nand), address(0){
	}

	void parse(int paramCount, char* param[]) override {
		if (paramCount != 1) {
			throw invalid_argument("Invalid Parameter Count");
		}

		for (const char ch : string(param[0])) {
			if ((ch >= '0') && (ch <= '9')) {
				continue;
			}
			throw invalid_argument("Invalid LBA");
		}

		int lba = atoi(param[0]);
		if (lba < 0 || lba > 99) {
			throw invalid_argument("LBA is out of range");
		}

		address = atoi(param[0]);
	}

	void run() override {
		nandIntf->read(address);
	}

private:
	int address;
	NANDInterface* nandIntf;
};