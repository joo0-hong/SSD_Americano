#include "FlushCmd.h"
#include <stdexcept>
#include <string>

using namespace std;

void FlushCmd::parse(int paramCount, char* param[]) {
	checkParamValid(paramCount, param);
}

void FlushCmd::run() {
	logger.print(__FUNCTION__, "Flush Command Start");
	nandDriver->flush();
}

void FlushCmd::checkParamValid(int paramCount, char* param[]) {
	checkParamCountValid(paramCount);
}
