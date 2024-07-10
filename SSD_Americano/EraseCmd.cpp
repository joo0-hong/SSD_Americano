#include "EraseCmd.h"
#include <string>
#include <stdexcept>

using namespace std;

void EraseCmd::parse(int paramCount, char* param[]) {
	checkParamValid(paramCount, param);

	address = atoi(param[0]);
	size = atoi(param[1]);
}

void EraseCmd::run() {
	nandIntf->erase(address, size);
}

void EraseCmd::checkParamValid(int paramCount, char* param[]) {
	checkParamCountValid(paramCount);
	checkLBAValid(param[0]);
	checkSizeValid(param[1]);
}

void EraseCmd::checkParamCountValid(int paramCount)
{
	if (paramCount == 2) {
		return;
	}

	throw invalid_argument("Invalid Parameter Count");
}

void EraseCmd::checkLBAValid(char* param)
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

void EraseCmd::checkSizeValid(char* param)
{
	for (const char ch : string(param)) {
		if ((ch >= '0') && (ch <= '9')) {
			continue;
		}
		throw invalid_argument("Invalid erase size");
	}

	int eraseSize = stoi(string(param));
	if ((eraseSize < 0) || (10 < eraseSize)) {
		throw invalid_argument("Invalid erase size");
	}
}

