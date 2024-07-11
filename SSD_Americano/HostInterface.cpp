#include "HostInterface.h"
#include "CommandFactory.h"

void HostInterface::processCommand(int argc, char* argv[])
{
	Command* command = nullptr;
	ARGUMENTS param = { };
	param.count = argc;
	param.value = argv;

	try {
		param = getNextArgument(param, false);
		string cmd = getCommandFromArgument(param);
		command = CommandFactory::newCommand(cmd, nandIntf);

		param = getNextArgument(param, false);
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
		command->parse(0, nullptr);
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

	return nextArgument;
}

string HostInterface::getCommandFromArgument(ARGUMENTS argument) {
	if (argument.count <= 0) {
		throw invalid_argument("Argument does not remain.");
	}
	return string(*argument.value);
}