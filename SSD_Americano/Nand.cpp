#pragma once
#include <iostream>
#include <fstream>

#include "NANDInterface.h"
#include "FileManager.cpp"

using namespace std;

class NAND : public NANDInterface {
public:
	void read(int lba) override
	{
		string result = nandFileManager.read(lba);
		resultFileManager.write(0, result);
	}

	void write(int lba, string data) override
	{
		nandFileManager.write(lba, data);
	}

	void error() override
	{
		resultFileManager.write(0, "NULL");
	}

private:
	const string RESULT_FILE = "TestResult.txt";
	const string NAND_FILE = "TestNand.txt";

	FileManager nandFileManager{ NAND_FILE };
	FileManager resultFileManager{ RESULT_FILE };
};