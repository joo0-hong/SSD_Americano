#pragma once
#include <string>
#include <stdexcept>
#include "CommandCommon.h"

using namespace std;

class WriteCmd : public CommandCommon {
public:
	WriteCmd(NANDDriver* nand) : nandDriver(nand), address(0), data("") {
	}

	void parse(int paramCount, char* param[]) override;
	void run() override;

private:
	const int PREFIX_SIZE = 2;
	const int DATA_SIZE = 10;

	NANDDriver* nandDriver;
	int address;
	string data;

	void checkParamValid(int paramCount, char* param[]);
	void checkParamCountValid(int paramCount);
	void checkDataValid(char* param);
};