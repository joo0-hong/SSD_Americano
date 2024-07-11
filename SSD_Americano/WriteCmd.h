#pragma once
#include "CommandCommon.h"
#include "NandInterface.h"
#include <string>
#include <stdexcept>

using namespace std;

class WriteCmd : public CommandCommon {
public:
	WriteCmd(NANDInterface* nand) : nandIntf(nand), address(0), data("") {
	}

	void parse(int paramCount, char* param[]) override;
	void run() override;

private:
	const int PREFIX_SIZE = 2;
	const int DATA_SIZE = 10;

	NANDInterface* nandIntf;
	int address;
	string data;

	void checkParamValid(int paramCount, char* param[]);
	void checkParamCountValid(int paramCount);
	void checkDataValid(char* param);
};