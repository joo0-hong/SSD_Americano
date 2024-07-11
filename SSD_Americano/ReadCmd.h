#pragma once
#include "CommandCommon.h"

class ReadCmd : public CommandCommon {
public:
	ReadCmd(NANDDriver* nand) : nandDriver(nand), address(0){
		suppParamCount = 1;
	}

	void parse(int paramCount, char* param[]) override;
	void run() override;

private:
	NANDDriver* nandDriver;
	int address;

	void checkParamValid(int paramCount, char* param[]);
};