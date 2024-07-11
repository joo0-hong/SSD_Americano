#pragma once
#include "CommandCommon.h"
#include "NandInterface.h"

class EraseCmd : public CommandCommon {
public:
	EraseCmd(NANDInterface* nand) : nandIntf(nand), address(0), size(0) {
	}

	void parse(int paramCount, char* param[]) override;
	void run() override;

private:
	NANDInterface* nandIntf;
	int address;
	int size;

	void checkParamValid(int paramCount, char* param[]);
	void checkParamCountValid(int paramCount);
	void checkSizeValid(char* param);
};