#include <iostream>
#include <fstream>
#include <string>

#include "TestShell.h"
#include "FileManager.h"

using namespace std;

TestShell::TestShell(const std::string& ssd_path
	, FileManager* fileManagerImpl)
	: SSD_PATH{ ssd_path }
	, fileManager{ fileManagerImpl } {}

void TestShell::write(std::string lba, std::string data) {
	string cmd("W");
	string ret = SSD_PATH + " " + cmd + " " + lba + " " + data;
	system(ret.c_str());
}

void TestShell::read(std::string lba) {
	invokeSSDRead(lba);

	std::cout << getSSDReadData() << std::endl;
}
void TestShell::invokeSSDRead(std::string& lba)
{
	string cmd("R");
	std::string ret = SSD_PATH + " " + cmd + " " + lba;
	system(ret.c_str());
}
string TestShell::getSSDReadData() {
	return fileManager->readFile();
}

void TestShell::exit() {}

void TestShell::help() {
}

void TestShell::fullwrite(std::string data) {
	for (int lba = 0; lba < 100; lba++) {
		write(std::to_string(lba), data);
	}
}

void TestShell::fullread() {
	for (int lba = 0; lba < 100; lba++) {
		read(std::to_string(lba));
	}
}

