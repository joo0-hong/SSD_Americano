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
		if (paramCount != 2) {
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

		for (const char ch : string(param[1])) {
			if ((ch >= '0') && (ch <= '9')) {
				continue;
			}
			throw invalid_argument("Invalid erase size");
		}

		int eraseSize = stoi(string(param[1]));
		if (eraseSize <= 0 && eraseSize > 10) {
			throw invalid_argument("Invalid erase size");
		}

		address = atoi(param[0]);
		size = atoi(param[1]);
	}

	void run() override {
		nandIntf->erase(address, size);
	}
private:
	int address;
	int size;
	NANDInterface* nandIntf;
};