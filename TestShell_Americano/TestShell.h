#pragma once
#include <string>

class TestShell {
public:
	void write(std::string lba, std::string data);
	void read(std::string lba);
	void exit();
	void help();
	void fullwrite();
	void fullread();
};