#include <stdexcept>
#include <string>
#include "ReadCmd.h"

using namespace std;

void ReadCmd::parse(int paramCount, char* param[]) {
	checkParamValid(paramCount, param);

	address = atoi(param[0]);
}

void ReadCmd::run() {
	logger.print(__FUNCTION__, "Read addr = " + to_string(address));
	nandDriver->read(address);
}

void ReadCmd::checkParamValid(int paramCount, char* param[]) {
	checkParamCountValid(paramCount);
	checkLBAValid(param[0]);
}


