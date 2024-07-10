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

void NAND::error()
{
	resultFileManager->write(0, "NULL");
}
