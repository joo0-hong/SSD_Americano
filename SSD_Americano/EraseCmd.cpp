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
	logger.print(__FUNCTION__, 
		"Erase addr = " + to_string(address) +" size= " + to_string(size));
	nandDriver->erase(address, size);
}

void EraseCmd::checkParamValid(int paramCount, char* param[]) {
	checkParamCountValid(paramCount);
	checkLBAValid(param[0]);
	checkSizeValid(param[1]);
}

void EraseCmd::checkSizeValid(char* param)
{
	if (false == isNumber(string(param))) {
		throw invalid_argument("Erase size is not a number");
	}

	if (false == isInRange(stoi(string(param)), 0, 10)) {
		throw invalid_argument("Erase size is not in range");
	}
}

