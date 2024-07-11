#pragma once
#include "CommandCommon.h"
#include "NandInterface.h"

class FlushCmd : public CommandCommon {
public:
	FlushCmd(NANDInterface* nand) : nandIntf(nand) {
	}

	void parse(int paramCount, char* param[]) override;
	void run() override;

private:
	NANDInterface* nandIntf;

	void checkParamValid(int paramCount, char* param[]);
	void checkParamCountValid(int paramCount);
};