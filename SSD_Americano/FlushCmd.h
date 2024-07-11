#pragma once
#include "CommandCommon.h"

class FlushCmd : public CommandCommon {
public:
	FlushCmd(NANDDriver* nand) : nandDriver(nand) {
	}

	void parse(int paramCount, char* param[]) override;
	void run() override;

private:
	NANDDriver* nandDriver;

	void checkParamValid(int paramCount, char* param[]);
	void checkParamCountValid(int paramCount);
};