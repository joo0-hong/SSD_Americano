#include "WriteCmd.h"

void WriteCmd::parse(int paramCount, char* param[]) {
	checkParamValid(paramCount, param);

	address = atoi(param[0]);
	data = param[1];
}

void WriteCmd::run() {
	nandDriver->write(address, data);
}

void WriteCmd::checkParamValid(int paramCount, char* param[]) {
	checkParamCountValid(paramCount);
	checkLBAValid(param[0]);
	checkDataValid(param[1]);
}

void WriteCmd::checkParamCountValid(int paramCount) {
	if (paramCount == 2) {
		return;
	}

	throw invalid_argument("Invalid Parameter Count");
}

void WriteCmd::checkDataValid(char* param) {
	string dataValue = string(param);

	if (dataValue.length() != DATA_SIZE) {
		throw invalid_argument("Invalid data length");
	}

	string dataPreFix = dataValue.substr(0, PREFIX_SIZE);
	if (dataPreFix != string("0x")) {
		throw invalid_argument("Invalid Data: Data should start with 0x");
	}

	string dataNumber = dataValue.substr(PREFIX_SIZE, dataValue.length());
	for (const char ch : dataNumber) {
		if (true == isInRange(ch, '0', '9')) {
			continue;
		}
		if (true == isInRange(ch, 'A', 'F')) {
			continue;
		}
		throw invalid_argument("Invalid Data:  Data should 0-9 or A-F");
	}
}
