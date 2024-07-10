#pragma once
#include <iostream>
#include <string>
#include "NandInterface.h"

using namespace std;

struct ARGUMENTS {
	int count;
	char** value;
};

class HostInterface {
public:
	HostInterface(NANDInterface* nand) : nandIntf(nand) { }

	void processCommand(int argc, char* argv[]);

private:
	NANDInterface* nandIntf;

	void processErrorCommand();
	ARGUMENTS getNextArgument(ARGUMENTS argument);
};