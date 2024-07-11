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

void ReadCmd::checkParamCountValid(int paramCount) {
	if (paramCount == 1) {
		return;
	}

	throw invalid_argument("Invalid Parameter Count");
}

