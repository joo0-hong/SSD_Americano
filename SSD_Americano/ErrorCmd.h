#pragma once
#include "Command.h"
#include "NandInterface.h"
#include "NandDriver.h"

class ErrorCmd : public Command {
public:
	ErrorCmd(NANDDriver* nand) : nandDriver(nand) {
	}

	void parse(int paramCount, char* param[]) override;
	void run() override;

private:
	NANDDriver* nandDriver;
};