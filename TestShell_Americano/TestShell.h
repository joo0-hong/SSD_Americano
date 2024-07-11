#pragma once
#include <string>
#include <map>
#include <vector>
#include <functional>

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
	void flush();

	bool testapp1();
	bool testapp2();

	bool run(std::string scenario);
	bool runCommand(std::string cmd, std::string arg1 = "", std::string arg2 = "", std::vector<std::string> expect_v = {});

	std::vector<std::string> getcmdresult();
	void setcmdresult(std::string result);
	void clearcmdresult();
	void setscenariomode();
	bool isscenariomode();

private:
	SSDDriver* ssdDriver_;
	FileReader* fileReader_;
	std::map<std::string, bool (TestShell::*)()> scenarioMap_;
	std::map<std::string, std::function<void(const std::string&, const std::string&)>> commandMap_;
	std::vector<std::string> cmdresult_;
	bool scenarioMode_;

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

	void setup();
};
