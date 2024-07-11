#include <string>
#include <stdexcept>
#include "EraseCmd.h"

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

	logger.print(__FUNCTION__, "Parameter count is not valid");
	throw invalid_argument("Invalid Parameter Count");
}

void EraseCmd::checkSizeValid(char* param)
{
	if (false == isNumber(string(param))) {
		logger.print(__FUNCTION__, "Erase size is not a number");
		throw invalid_argument("Invalid erase size");
	}

	if (false == isInRange(stoi(string(param)), 0, 10)) {
		logger.print(__FUNCTION__, "Erase size is not in range");
		throw invalid_argument("Invalid erase size");
	}
}

