#pragma once
#include <string>

using namespace std;
#define interface struct

interface NANDInterface {
public:
	virtual void read(int lba) = 0;
	virtual void write(int lba, string data) = 0;
};

class Nand : public NANDInterface {
public:
	static Nand& getInstance() {
		static Nand nand;
		return nand;
	}
	Nand() {

	}
	void read(int lba) {
	
	}
	void write(int lba, string data) {
	}
private:
	Nand& operator=(const Nand& other) = delete;
	Nand(const Nand& other) = delete;
};