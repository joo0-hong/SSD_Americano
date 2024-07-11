#include "HostInterface.h"
#include "Nand.h"
#include "NandBuffer.h"

const string RESOURCE_PATH = "..\\..\\resources\\";
const string NAND_FILE = "nand.txt";
const string RESULT_FILE = "result.txt";
const string BUFFER_FILE = "buffer.txt";

int main(int argc, char* argv[])
{
	NANDInterface* nand = new NAND(RESOURCE_PATH + NAND_FILE, RESOURCE_PATH + RESULT_FILE);
	NANDBuffer* buffer = new NANDBuffer(RESOURCE_PATH + BUFFER_FILE);
	HostInterface* hostIntf = new HostInterface(nand, buffer);

	hostIntf->processCommand(argc, argv);

	delete hostIntf;
	delete buffer;
	delete nand;
}