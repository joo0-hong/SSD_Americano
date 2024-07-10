#include "ReadCmd.h"
#include <stdexcept>
#include <string>

using namespace std;

void ReadCmd::parse(int paramCount, char* param[]) {
	checkParamValid(paramCount, param);

	address = atoi(param[0]);
}

void ReadCmd::run() {
	nandIntf->read(address);
}

void ReadCmd::checkParamValid(int paramCount, char* param[]) {
	checkParamCountValid(paramCount);
	checkLBAValid(param[0]);
}

void ReadCmd::checkParamCountValid(int paramCount)
{
	if (paramCount == 1) {
		return;
	}

	throw invalid_argument("Invalid Parameter Count");
}

void ReadCmd::checkLBAValid(char* param)
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
