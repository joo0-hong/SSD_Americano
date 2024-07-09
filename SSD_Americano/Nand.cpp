#pragma once
#include <iostream>
#include <fstream>

#include "NANDInterface.h"
#include "FileManager.cpp"

using namespace std;

class NAND : public NANDInterface {
public:
	NAND(string nandFile, string resultFile)
	{
		nandFileManager = new FileManager{ nandFile };
		resultFileManager = new FileManager{ resultFile };
	}

	~NAND()
	{
		delete nandFileManager;
		delete resultFileManager;
	}

	void read(int lba) override
	{
		string result = nandFileManager->read(lba);
		resultFileManager->write(0, result);
	}

	void write(int lba, string data) override
	{
		nandFileManager->write(lba, data);
	}

	void error() override
	{
		resultFileManager->write(0, "NULL");
	}

private:
	FileManager* nandFileManager;
	FileManager* resultFileManager;
};