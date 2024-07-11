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
	nandDriver->erase(address, size);
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

void EraseCmd::checkSizeValid(char* param)
{
	if (false == isNumber(string(param))) {
		throw invalid_argument("Invalid erase size");
	}

	if (false == isInRange(stoi(string(param)), 0, 10)) {
		throw invalid_argument("Invalid erase size");
	}
}

