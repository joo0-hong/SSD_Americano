#include <iostream>
#include <fstream>
#include <string>

#include "FileManager.h"

using namespace std;

class TestShell {
public:
	TestShell(const std::string& ssd_path
		, FileManager* fileManagerImpl)
		: SSD_PATH{ ssd_path }
		, fileManager{ fileManagerImpl } {}

	void write(std::string lba, std::string data) {
		string cmd("W");
		string ret = SSD_PATH + " " + cmd + " " + lba + " " + data;
		system(ret.c_str());
	}

	void read(std::string lba) {
		invokeSSDRead(lba);

		std::cout << getSSDReadData() << std::endl;
	}
	void exit() {
	}
	void help() {
		helpWrite();
		helpRead();
		helpFullWrite();
		helpFullRead();
		helpHelp();
		helpExit();
	}
	void fullwrite(std::string data) {
		for (int lba = 0; lba < 100; lba++) {
			write(std::to_string(lba), data);
		}
	}
	void fullread() {
		for (int lba = 0; lba < 100; lba++) {
			read(std::to_string(lba));
		}
	}

private:
	const std::string SSD_PATH;
	const std::string RESULT_PATH;

	FileManager* fileManager;

	void invokeSSDRead(std::string& lba)
	{
		string cmd("R");
		std::string ret = SSD_PATH + " " + cmd + " " + lba;
		system(ret.c_str());
	}
	std::string getSSDReadData() {
		return fileManager->readFile();
	} 

	void helpExit() const
	{
		std::cout << "======================================================" << std::endl;
		std::cout << "[NAME]" << std::endl;
		std::cout << "exit" << std::endl << std::endl;
		std::cout << "[SYNOPSIS]" << std::endl;
		std::cout << "- exit []" << std::endl << std::endl;
		std::cout << "[DESCRIPTION]" << std::endl;
		std::cout << "- exit the Test Shell" << std::endl;
		std::cout << "======================================================" << std::endl << std::endl;
	}
	void helpHelp() const
	{
		std::cout << "======================================================" << std::endl;
		std::cout << "[NAME]" << std::endl;
		std::cout << "help" << std::endl << std::endl;
		std::cout << "[SYNOPSIS]" << std::endl;
		std::cout << "- help []" << std::endl << std::endl;
		std::cout << "[DESCRIPTION]" << std::endl;
		std::cout << "- dispaly help information about the Test Shell" << std::endl;
		std::cout << "======================================================" << std::endl << std::endl;
	}
	void helpFullRead() const
	{
		std::cout << "======================================================" << std::endl;
		std::cout << "[NAME]" << std::endl;
		std::cout << "fullread" << std::endl << std::endl;
		std::cout << "[SYNOPSIS]" << std::endl;
		std::cout << "- fullread []" << std::endl << std::endl;
		std::cout << "[DESCRIPTION]" << std::endl;
		std::cout << "- read data from LBA #0 to #99" << std::endl;
		std::cout << "======================================================" << std::endl << std::endl;
	}
	void helpFullWrite() const
	{
		std::cout << "======================================================" << std::endl;
		std::cout << "[NAME]" << std::endl;
		std::cout << "fullwrite" << std::endl << std::endl;
		std::cout << "[SYNOPSIS]" << std::endl;
		std::cout << "- fullwrite [DATA]" << std::endl << std::endl;
		std::cout << "[DESCRIPTION]" << std::endl;
		std::cout << "- write data from LBA #0 to #99" << std::endl;
		std::cout << "======================================================" << std::endl << std::endl;
	}
	void helpRead() const
	{
		std::cout << "======================================================" << std::endl;
		std::cout << "[NAME]" << std::endl;
		std::cout << "read" << std::endl;
		std::cout << "[SYNOPSIS]" << std::endl;
		std::cout << "- read [LBA]" << std::endl;
		std::cout << "[DESCRIPTION]" << std::endl;
		std::cout << "- read data from LBA" << std::endl;
		std::cout << "======================================================" << std::endl << std::endl;

	}
	void helpWrite() const
	{
		std::cout << "======================================================" << std::endl;
		std::cout << "[NAME]" << std::endl;
		std::cout << "write" << std::endl << std::endl;
		std::cout << "[SYNOPSIS]" << std::endl;
		std::cout << "- write [LBA] [DATA]" << std::endl << std::endl;
		std::cout << "[DESCRIPTION]" << std::endl;
		std::cout << "- write data to LBA" << std::endl;
		std::cout << "======================================================" << std::endl << std::endl;
	}
};