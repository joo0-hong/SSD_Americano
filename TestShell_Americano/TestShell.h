#pragma once
#include <string>

#include "SSDDriver.h"
#include "FileReader.h"

class TestShell {
public:
	TestShell(SSDDriver* ssdDriver
		, FileReader* fileReader);

	void write(std::string lba, std::string data);
	void read(std::string lba);
	void exit();
	void help();
	void fullwrite(std::string data);
	void fullread();
private:
	SSDDriver* ssdDriver_;
	FileReader* fileReader_;

	void invokeSSDRead(const std::string& lba);
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