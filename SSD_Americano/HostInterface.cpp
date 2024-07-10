#include "HostInterface.h"
#include "CommandFactory.h"

void HostInterface::processCommand(int argc, char* argv[])
{
	Command* command = nullptr;
	ARGUMENTS param = { };
	param.count = argc;
	param.value = argv;

	try {
		param = getNextArgument(param);
		string cmd = string(*param.value);
		command = CommandFactory::newCommand(cmd, nandIntf);

		param = getNextArgument(param);
		command->parse(param.count, param.value);
		command->run();
	}
	catch (...) {
		processErrorCommand();
	}

	if (nullptr != command) {
		delete command;
	}
}

void HostInterface::processErrorCommand() {
	Command* command = nullptr;

	try {
		command = CommandFactory::newErrorCommand(nandIntf);
		command->run();
	}
	catch (...) {
		; // Logging
	}

	if (nullptr != command) {
		delete command;
	}
}

ARGUMENTS HostInterface::getNextArgument(ARGUMENTS argument) {
	ARGUMENTS nextArgument = argument;
	nextArgument.count--;
	nextArgument.value++;

	if (nextArgument.count <= 0) {
		throw invalid_argument("Argument does not remain.");
	}

	return nextArgument;
}