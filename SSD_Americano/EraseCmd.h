#pragma once
#include "CommandCommon.h"

class EraseCmd : public CommandCommon {
public:
	EraseCmd(NANDDriver* nand) : nandDriver(nand), address(0), size(0) {
	}

	void parse(int paramCount, char* param[]) override;
	void run() override;

private:
	NANDDriver* nandDriver;
	int address;
	int size;

	void checkParamValid(int paramCount, char* param[]);
	void checkParamCountValid(int paramCount);
	void checkSizeValid(char* param);
};