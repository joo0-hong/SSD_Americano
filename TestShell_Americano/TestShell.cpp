#include <iostream>
#include <fstream>
#include <string>

#include "TestShell.h"
#include "FileReader.h"

using namespace std;

TestShell::TestShell(const std::string& ssd_path
	, FileReader* fileReader)
	: SSD_PATH{ ssd_path }
	, fileReader_{ fileReader } {}

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
	return fileReader_->readFile();
}
void TestShell::exit() {
}
void TestShell::help() {
	helpWrite();
	helpRead();
	helpExit();
	helpHelp();
	helpFullWrite();
	helpFullRead();
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

void TestShell::helpWrite() const {
	string name{ "write" };
	string synopsis{ "write [LBA] [DATA]" };
	string description{ "write data to LBA" };

	displayHelp(name, synopsis, description);
}

void TestShell::helpRead() const {
	string name{ "read" };
	string synopsis{ "read [LBA]" };
	string description{ "read data from LBA" };

	displayHelp(name, synopsis, description);
}

void TestShell::helpExit() const {
	string name{ "exit" };
	string synopsis{ "exit []" };
	string description{ "exit the Test Shell" };

	displayHelp(name, synopsis, description);
}

void TestShell::helpHelp() const {
	string name{ "help" };
	string synopsis{ "help []" };
	string description{ "dispaly help information about the Test Shell" };

	displayHelp(name, synopsis, description);
}

void TestShell::helpFullRead() const {
	string name{ "fullread" };
	string synopsis{ "fullread []" };
	string description{ "read data from LBA #0 to #99" };

	displayHelp(name, synopsis, description);
}

void TestShell::helpFullWrite() const {
	string name{ "fullwrite" };
	string synopsis{ "fullwrite [DATA]" };
	string description{ "write data from LBA #0 to #99" };

	displayHelp(name, synopsis, description);
}

void TestShell::displayHelp(const std::string& name, const std::string& synopsis, const std::string& description)  const {
	std::cout << "======================================================" << std::endl;
	std::cout << "[NAME]" << std::endl;
	std::cout << name << std::endl << std::endl;
	std::cout << "[SYNOPSIS]" << std::endl;
	std::cout << "- " << synopsis << std::endl << std::endl;
	std::cout << "[DESCRIPTION]" << std::endl;
	std::cout << "- " << description << std::endl;
	std::cout << "======================================================" << std::endl << std::endl;
}