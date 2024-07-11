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
	bool exit();
	void help();
	void fullwrite(std::string data);
	void fullread();
	void erase(std::string lba, std::string zise);
	void erase_range(std::string start_lba, std::string end_lba);
	bool testapp1();
	bool testapp2();
	void flush() {};

	bool run(std::string scenario);

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
