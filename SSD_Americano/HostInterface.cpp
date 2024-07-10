#include "HostInterface.h"
#include "CommandFactory.h"

void HostInterface::processCommand(int argc, char* argv[])
{
	Command* cmd = nullptr;

	try {
		if (argc < 2) {
			throw invalid_argument("There is no argument.");
		}

		cmd = CommandFactory::getNewCommand(string(argv[1]), nandIntf);

		cmd->parse(argc - 2, &argv[2]);
		cmd->run();
	}
	catch (...) {
		delete cmd;
		cmd = new ErrorCmd(nandIntf);
		cmd->run();
	}

	delete cmd;
}

