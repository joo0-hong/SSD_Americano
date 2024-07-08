#pragma once
#include <string>

class TestShell {
public:
	void write(std::string cmd, std::string lba, std::string data);
	void read(std::string cmd, std::string lba);
	void exit();
	void help();
	void fullwrite();
	void fullread();
};