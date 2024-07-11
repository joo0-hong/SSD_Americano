#include "FlushCmd.h"
#include <stdexcept>
#include <string>

using namespace std;

void FlushCmd::parse(int paramCount, char* param[]) {
	checkParamValid(paramCount, param);
}

void FlushCmd::run() {
	nandDriver->flush();
}

void FlushCmd::checkParamValid(int paramCount, char* param[]) {
	checkParamCountValid(paramCount);
}

void FlushCmd::checkParamCountValid(int paramCount) {
	if (paramCount == 0) {
		return;
	}

	throw invalid_argument("Invalid Parameter Count");
}

