#include "HostInterface.cpp"
#include "Nand.cpp"

int main(int argc, char* argv[])
{
	NANDInterface* nand = new NAND("TestNandFile.txt", "TestResultFile.txt");
	HostInterface* hostIntf = new HostInterface(nand);

	hostIntf->processCommand(argc, argv);

	delete nand;
	delete hostIntf;
}