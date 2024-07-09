#include <iostream>
#include <fstream>
#include <string>

#include "TestShell.h"
#include "FileReader.h"

using namespace std;

TestShell::TestShell(SSDDriver* ssdDriver
	, FileReader* fileReader)
	: ssdDriver_{ ssdDriver }
	, fileReader_{ fileReader } {}

void TestShell::write(const std::string lba, const std::string data) {
	ssdDriver_->write(lba, data);
}

void TestShell::read(std::string lba) {
	invokeSSDRead(lba);

	std::cout << getSSDReadData() << std::endl;
}
void TestShell::invokeSSDRead(const std::string& lba)
{
	ssdDriver_->read(lba);
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

bool TestShell::testApp2() {
	for (int i = 0; i < 30; i++) {
		write("0", "0xAAAABBBB");
		write("1", "0xAAAABBBB");
		write("2", "0xAAAABBBB");
		write("3", "0xAAAABBBB");
		write("4", "0xAAAABBBB");
		write("5", "0xAAAABBBB");
	}
	
	write("0", "0x12345678");
	write("1", "0x12345678");
	write("2", "0x12345678");
	write("3", "0x12345678");
	write("4", "0x12345678");
	write("5", "0x12345678");

	read("0");
	if ("0x12345678" != getSSDReadData())
		return false;

	read("1");
	if ("0x12345678" != getSSDReadData())
		return false;

	read("2");
	if ("0x12345678" != getSSDReadData())
		return false;

	read("3");
	if ("0x12345678" != getSSDReadData())
		return false;

	read("4");
	if ("0x12345678" != getSSDReadData())
		return false;

	read("5");
	if ("0x12345678" != getSSDReadData())
		return false;

	return true;
}