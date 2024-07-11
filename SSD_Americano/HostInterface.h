#pragma once
#include <iostream>
#include <string>
#include "NandInterface.h"
#include "NandBuffer.h"
#include "NandDriver.h"
#include "Logger.h"

using namespace std;

struct ARGUMENTS {
	int count;
	char** value;
};

class HostInterface {
public:
	HostInterface(NANDInterface* nand, NANDBuffer* buffer) : driver(new NANDDriver(nand, buffer)) { }

	void processCommand(int argc, char* argv[]);

private:
	NANDDriver* driver;
	Logger& logger = Logger::getInstance();
	void processErrorCommand();
	ARGUMENTS getNextArgument(ARGUMENTS argument);
	string getCommandFromArgument(ARGUMENTS argument);
};