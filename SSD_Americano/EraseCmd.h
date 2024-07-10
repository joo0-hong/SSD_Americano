#pragma once
#include "Command.h"
#include "NandInterface.h"
#include <string>

using namespace std;

class EraseCmd : public Command {
public:
	EraseCmd(NANDInterface* nand) : nandIntf(nand), address(0), size(0) {
	}

	void parse(int paramCount, char* param[]) override {
		checkParamValid(paramCount, param);

		address = atoi(param[0]);
		size = atoi(param[1]);
	}

	void run() override {
		nandIntf->erase(address, size);
	}

private:
	NANDInterface* nandIntf;
	int address;
	int size;

	void checkParamValid(int paramCount, char* param[]) {
		checkParamCountValid(paramCount);
		checkLBAValid(param[0]);
		checkSizeValid(param[1]);
	}

	void checkParamCountValid(int paramCount)
	{
		if (paramCount == 2) {
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

	void checkSizeValid(char* param)
	{
		for (const char ch : string(param)) {
			if ((ch >= '0') && (ch <= '9')) {
				continue;
			}
			throw invalid_argument("Invalid erase size");
		}

		int eraseSize = stoi(string(param));
		if (eraseSize <= 0 && eraseSize > 10) {
			throw invalid_argument("Invalid erase size");
		}
	}
};