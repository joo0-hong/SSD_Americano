#pragma once
#include "CommandCommon.h"
#include "NandInterface.h"

class ReadCmd : public CommandCommon {
public:
	ReadCmd(NANDInterface* nand) : nandIntf(nand), address(0){
	}

	void parse(int paramCount, char* param[]) override;
	void run() override;

private:
	NANDInterface* nandIntf;
	int address;

	void checkParamValid(int paramCount, char* param[]);
	void checkParamCountValid(int paramCount);
};