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
};