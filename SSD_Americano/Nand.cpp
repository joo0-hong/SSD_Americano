#include "Nand.h"

NAND::NAND(string nandFile, string resultFile)
{
	nandFileManager = new FileManager{ nandFile };
	resultFileManager = new FileManager{ resultFile };
}

NAND::~NAND()
{
	delete nandFileManager;
	delete resultFileManager;
}

void NAND::read(int lba)
{
	string result = nandFileManager->read(lba);
	writeResult(result);
}

void NAND::write(int lba, string data)
{
	nandFileManager->write(lba, data);
}

void NAND::erase(const int lba, const int size) {
	int actualSize = size;

	if (lba + actualSize - 1 > MAX_ADDR) {
		actualSize = actualSize - (lba + actualSize - 1 - MAX_ADDR);
	}

	for (int addr = lba; addr < lba + actualSize; addr++) {
		nandFileManager->write(addr, INITIAL_DATA);
	}
}

void NAND::error()
{
	writeResult("NULL");
}

void NAND::writeResult(string result)
{
	resultFileManager->write(0, result);
}
