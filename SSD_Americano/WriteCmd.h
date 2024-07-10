#pragma once
#include "Command.h"
#include "NandInterface.h"
#include <string>
#include <stdexcept>

using namespace std;

class WriteCmd : public Command {
public:
	WriteCmd(NANDInterface* nand) : nandIntf(nand), address(0), data("") {
	}

	void parse(int paramCount, char* param[]) override;
	void run() override;

private:
	NANDInterface* nandIntf;
	int address;
	string data;

	void checkParamValid(int paramCount, char* param[]);
	void checkParamCountValid(int paramCount);
	void checkLBAValid(char* param);
	void checkDataValid(char* param);
};