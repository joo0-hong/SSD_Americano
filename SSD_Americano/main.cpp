#include "HostInterface.h"
#include "Nand.h"
#include "NandBuffer.h"

int main(int argc, char* argv[])
{
	NANDInterface* nand = new NAND("../../resources/nand.txt", "../../resources/result.txt");
	NANDBuffer* buffer = new NANDBuffer("../../resources/buffer.txt");
	HostInterface* hostIntf = new HostInterface(nand, buffer);

	hostIntf->processCommand(argc, argv);

	delete nand;
	delete hostIntf;
}