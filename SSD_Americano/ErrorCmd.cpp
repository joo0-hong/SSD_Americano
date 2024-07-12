#include "ErrorCmd.h"

void ErrorCmd::parse(int paramCount, char* param[]) {
	return;
}

void ErrorCmd::run() {
	logger.print(__FUNCTION__, "Error Command Start");
	nandDriver->error();
}
