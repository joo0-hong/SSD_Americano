#include "ErrorCmd.h"

void ErrorCmd::parse(int paramCount, char* param[]) {
	return;
}

void ErrorCmd::run() {
	nandDriver->error();
}
