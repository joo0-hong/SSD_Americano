#pragma once
#include "Command.h"
#include "NandInterface.h"

class ErrorCmd : public Command {
public:
	ErrorCmd(NANDInterface* nand) : nandIntf(nand) {
	}

	void parse(int paramCount, char* param[]) override;
	void run() override;

private:
	NANDInterface* nandIntf;
};