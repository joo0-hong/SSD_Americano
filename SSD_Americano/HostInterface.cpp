#include "HostInterface.h"
#include "CommandFactory.h"

void HostInterface::processCommand(int argc, char* argv[])
{
	Command* command = nullptr;
	ARGUMENTS param = { };
	param.count = argc;
	param.value = argv;

	logger.print(__FUNCTION__, "New Command Started");

	try {
		param = getNextArgument(param);
		string cmd = getCommandFromArgument(param);
		command = CommandFactory::newCommand(cmd, driver);

		param = getNextArgument(param);
		command->parse(param.count, param.value);
		command->run();
	}
	catch (exception e) {
		logger.print(__FUNCTION__,  "<EXCEPTION> " + string(e.what()));
		processErrorCommand();
	}

	if (nullptr != command) {
		delete command;
	}

	logger.print(__FUNCTION__, "Command Completed");
}

void HostInterface::processErrorCommand() {
	Command* command = nullptr;

	try {
		command = CommandFactory::newErrorCommand(driver);
		command->parse(0, nullptr);
		command->run();
	}
	catch (exception e) {
		logger.print(__FUNCTION__, "<EXCEPTION> " + string(e.what()));
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