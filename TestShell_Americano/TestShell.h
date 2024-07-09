#pragma once
#include <string>

#include "FileManager.h"

class TestShell {
public:
	TestShell(const std::string& ssd_path
		, FileManager* fileManagerImpl);

	void write(std::string lba, std::string data);
	void read(std::string lba);
	void exit();
	void help();
	void fullwrite(std::string data);
	void fullread();
private:
	const std::string SSD_PATH;
	const std::string RESULT_PATH;

	FileManager* fileManager;

	void invokeSSDRead(std::string& lba);
	std::string getSSDReadData();
};