#include "HostInterface.h"
#include "Nand.h"

int main(int argc, char* argv[])
{
	NANDInterface* nand = new NAND("../../resources/nand.txt", "../../resources/result.txt");
	HostInterface* hostIntf = new HostInterface(nand);

	hostIntf->processCommand(argc, argv);

	delete nand;
	delete hostIntf;
}