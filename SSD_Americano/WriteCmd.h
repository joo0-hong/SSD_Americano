#pragma once
#include "Command.h"
#include "NandInterface.h"
#include <string>
#include <stdexcept>

using namespace std;

class WriteCmd : public Command {
public:
	WriteCmd(NANDInterface* nand) : nandIntf(nand), address(0), data("") {
	}

	void parse(int paramCount, char* param[]) override {
		checkParamValid(paramCount, param);

		address = atoi(param[0]);
		data = param[1];
	}

	void run() override {
		nandIntf->write(address, data);
	}

private:
	NANDInterface* nandIntf;
	int address;
	string data;

	void checkParamValid(int paramCount, char* param[]) {
		checkParamCountValid(paramCount);
		checkLBAValid(param[0]);
		checkDataValid(param[1]);
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

	void checkDataValid(char* param)
	{
		string dataValue = string(param);

		if (dataValue.length() != 10) {
			throw invalid_argument("Invalid data length");
		}

		string dataPreFix = dataValue.substr(0, 2);
		if (dataPreFix != string("0x")) {
			throw invalid_argument("Invalid Data: Data should start with 0x");
		}
		string dataNumber = dataValue.substr(2, dataValue.length());
		for (const char ch : dataNumber) {
			if ((ch >= '0') && (ch <= '9')) {
				continue;
			}
			if ((ch >= 'A') && (ch <= 'F'))
			{
				continue;
			}
			throw invalid_argument("Invalid Data:  Data should 0-9 or A-F");
		}
	}
};