#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "TestShell.h"
#include "FileReader.h"


using namespace std;

TestShell::TestShell(SSDDriver* ssdDriver
	, FileReader* fileReader)
	: ssdDriver_{ ssdDriver }
	, fileReader_{ fileReader }
	, scenarioMode_{ false } {
	setup();
}

void TestShell::setup() {
	scenarioMap_["testapp1"] = &TestShell::testapp1;
	scenarioMap_["testapp2"] = &TestShell::testapp2;

	commandMap_ = {
			{"write", [&](const std::string& arg1, const std::string& arg2) { write(arg1, arg2); }},
			{"read", [&](const std::string& arg1, const std::string&) { read(arg1); }},
			{"help", [&](const std::string&, const std::string&) { help(); }},
			{"fullwrite", [&](const std::string& arg1, const std::string&) { fullwrite(arg1); }},
			{"fullread", [&](const std::string&, const std::string&) { fullread(); }},
			{"erase", [&](const std::string& arg1, const std::string& arg2) { erase(arg1, arg2); }},
			{"erase_range", [&](const std::string& arg1, const std::string& arg2) { erase_range(arg1, arg2); }},
			{"flush", [&](const std::string&, const std::string&) { flush(); }}
	};
}

void TestShell::setscenariomode(bool mode) {
	scenarioMode_ = mode;
}
bool TestShell::isscenariomode() {
	return scenarioMode_;
}

bool TestShell::runCommand(std::string cmd, std::string arg1, std::string arg2, std::vector<std::string> expect_v) {
	clearcmdresult();

	auto it = commandMap_.find(cmd);
	if (it == commandMap_.end()) {
		return false;
	}

	int size = expect_v.size();
	it->second(arg1, arg2);
	
	if (size <= 0)
		return true;

	std::vector<std::string> actual_v = getcmdresult();
	for (int i = 0; i < size; i++) {
		if (expect_v[i] != actual_v[i])
			return false;
	}

	return true;
}

std::vector<std::string> TestShell::getcmdresult() {
	return cmdresult_;
}

void TestShell::clearcmdresult() {
	cmdresult_.clear();
}

void TestShell::setcmdresult(std::string result) {
	cmdresult_.push_back(result);
}

void TestShell::write(const std::string lba, const std::string data) {
	ssdDriver_->write(lba, data);
}

void TestShell::read(std::string lba) {
	invokeSSDRead(lba);
	if (isscenariomode()) {
		setcmdresult(getSSDReadData());
	}
	else {
		std::cout << getSSDReadData() << std::endl;
	}
}
void TestShell::invokeSSDRead(const std::string& lba)
{
	ssdDriver_->read(lba);
}

void TestShell::flush()
{
	ssdDriver_->flush();
}

string TestShell::getSSDReadData() {
	return fileReader_->readFile();
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

bool TestShell::testapp1() {
	fullwrite("0x11111111");
	fullread();

	std::vector<std::string> actual_v = getcmdresult();
	for (auto actualData : actual_v) {
		if ("0x11111111" != actualData)
			return false;
	}

	return true;
}

bool TestShell::testapp2() {
	vector<string> LBA = { "0", "1", "2", "3", "4", "5" };
	const int iter_max = 30;

	string data = "0xAAAABBBB";
	for (int iter = 0; iter < iter_max; iter++) {
		for (auto lba : LBA) {
			write(lba, data);
		}
	}
	
	data = "0x12345678";
	for (auto lba : LBA) {
		write(lba, data);
		read(lba);
		
		if (data != getSSDReadData())
			return false;
	}

	return true;
}

void TestShell::erase(std::string lba, std::string size) {
	int total_size = std::stoi(size);
	if (total_size > 100) {
		total_size = 100;
	}
	int lba_start = std::stoi(lba);
	const int ERASE_LBA_MAX = 10;
	const int LBA_MAX = 100;

	while (lba_start < LBA_MAX) {
		int lba_size = (total_size <= ERASE_LBA_MAX) ? total_size : ERASE_LBA_MAX;
		ssdDriver_->erase(std::to_string(lba_start), std::to_string(lba_size));

		if (total_size <= ERASE_LBA_MAX) {
			break;
		}

		lba_start += ERASE_LBA_MAX;
		total_size -= ERASE_LBA_MAX;
	}
}

void TestShell::erase_range(std::string start_lba, std::string end_lba) {
	int total_size = std::stoi(end_lba) - std::stoi(start_lba);
	erase(start_lba, std::to_string(total_size));
}

bool TestShell::run(std::string scenario) {
	if (scenarioMap_.find(scenario) == scenarioMap_.end()) {
		return false;
	}
	return (this->*scenarioMap_[scenario])();
}
