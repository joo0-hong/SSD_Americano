#pragma once
#include <iostream>
#include <fstream>

#include "NANDInterface.h"
#include "FileManager.h"

using namespace std;

class NAND : public NANDInterface {
public:
	NAND(string nandFile, string resultFile);
	~NAND();

	void read(int lba) override;
	void write(int lba, string data) override;
	void error() override;

private:
	FileManager* nandFileManager;
	FileManager* resultFileManager;
};