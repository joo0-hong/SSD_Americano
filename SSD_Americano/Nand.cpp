#include "Nand.h"
#pragma once

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
	resultFileManager->write(0, result);
}

void NAND::write(int lba, string data)
{
	nandFileManager->write(lba, data);
}

void NAND::erase(int lba, string size) {
	int actualSize = stoi(size);

	if (actualSize > MAX_ERASE_SIZE) {
		actualSize = MAX_ERASE_SIZE;
	}
	if (lba + actualSize - 1 > MAX_ADDR) {
		actualSize = actualSize - (lba + actualSize - 1 - MAX_ADDR);
	}

	for (int addr = lba; addr < lba + actualSize; addr++) {
		nandFileManager->write(addr, INITIAL_DATA);
	}
}

void NAND::error()
{
	resultFileManager-> write(0, "NULL");
}
