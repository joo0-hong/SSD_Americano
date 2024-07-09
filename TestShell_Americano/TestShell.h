#pragma once
#include <string>

#include "FileReader.h"

class TestShell {
public:
	TestShell(const std::string& ssd_path
		, FileReader* fileReader);

	void write(std::string lba, std::string data);
	void read(std::string lba);
	void exit();
	void help();
	void fullwrite(std::string data);
	void fullread();
private:
	const std::string SSD_PATH;

	FileReader* fileReader_;

	void invokeSSDRead(std::string& lba);
	std::string getSSDReadData();

	void helpExit() const;
	void helpHelp() const;
	void helpFullRead() const;
	void helpFullWrite() const;
	void helpRead() const;
	void helpWrite() const;
	void displayHelp(const std::string& name
		, const std::string& synopsis
		, const std::string& description) const;
};