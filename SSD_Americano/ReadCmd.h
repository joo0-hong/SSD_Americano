#pragma once
#include "Command.h"
#include "NandInterface.h"

class ReadCmd : public Command {
public:
	ReadCmd(NANDInterface* nand) : nandIntf(nand), address(0){
	}

	void parse(int paramCount, char* param[]) override {
		checkParamValid(paramCount, param);

		address = atoi(param[0]);
	}

	void run() override {
		nandIntf->read(address);
	}

private:
	NANDInterface* nandIntf;
	int address;

	void checkParamValid(int paramCount, char* param[]) {
		checkParamCountValid(paramCount);
		checkLBAValid(param[0]);
	}

	void checkParamCountValid(int paramCount)
	{
		if (paramCount == 1) {
			return;
		}

		throw invalid_argument("Invalid Parameter Count");
	}

	void checkLBAValid(char* param)
	{
		for (const char ch : string(param)) {
			if ((ch >= '0') && (ch <= '9')) {
				continue;
			}
			throw invalid_argument("Invalid LBA");
		}

		int lba = atoi(param);
		if (lba < 0 || lba > 99) {
			throw invalid_argument("LBA is out of range");
		}
	}
};