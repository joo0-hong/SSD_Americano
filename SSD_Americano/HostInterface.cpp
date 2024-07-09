#include <iostream>
#include <string>
#include "NandInterface.h"
using namespace std;

static const int READ = 1;
static const int WRITE = 2;

interface Command {
	virtual void run() = 0;
};

class ReadCmd : public Command {
public:
	ReadCmd(int addr, NANDInterface* nand) : address(addr), nandIntf(nand){
	}
	void run() override {
		nandIntf->read(address);
	}
private:
	int address;
	NANDInterface* nandIntf;
};

class WriteCmd : public Command {
public:
	WriteCmd(int addr, string data, NANDInterface* nand) : address(addr), data(data), nandIntf(nand) {
	}
	void run() override {
		nandIntf->write(address,data);
	}
private:
	int address;
	string data;
	NANDInterface* nandIntf;
};

class ErrorCmd : public Command {
public:
	ErrorCmd(NANDInterface* nand) : nandIntf(nand){
	}
	void run() override {
		// Ask File Mgr to write "NULL"
	}
private:
	int address;
	NANDInterface* nandIntf;
};

class HostInterface {
public:
	HostInterface(NANDInterface* nand) : nandIntf(nand) {}
	void parseCommand(int argc, char* argv[]) {
		if (string(argv[1]) == "W") {
			command = WRITE;
			data = string(argv[3]);
		}
		else if (string(argv[1]) == "R") {
			command = READ;
		}
		else {
			cout << "PARSING ERROR : " << command << endl;
		}

		addr = atoi(argv[2]);
	}

	bool checkInvalidCommand(int argc, char* argv[]) {
		if (argc < MIN_VALID_ARGUMENT_NUM) {
			return true;
		}

		if (string(argv[1]) != "R" && string(argv[1]) != "W") {
			return true;
		}

		if (string(argv[1]) == "R" && argc != VALID_READ_ARGUMENT_NUM) {
			return true;
		}

		if (string(argv[1]) == "W" && argc != VALID_WRITE_ARGUMENT_NUM) {
			return true;
		}

		if (string(argv[1]) == "R" || string(argv[1]) == "W") {
			for (const char ch : string(argv[2])) {
				if ((ch >= '0') && (ch <= '9')) {
					continue;
				}
				cout << "Invalid LBA !!!" << endl;
				return true;
			}
			int lba = atoi(argv[2]);
			if (lba < MIN_LBA || lba > MAX_LBA) {
				return true;
			}
		}

		if (string(argv[1]) == "W") {
			string data = string(argv[3]);

			if (data.length() != DATA_LENGTH) {
				cout << "Invalid data length !!!" << endl;
				return true;
			}
			string dataPreFix = data.substr(0, 2);
			if (dataPreFix != string("0x")) {
				cout << "Invalid Data: Data should start with 0x !!! " << dataPreFix << endl;
				return true;
			}
			string dataNumber = data.substr(2, data.length());
			for (const char ch : dataNumber) {
				if ((ch >= '0') && (ch <= '9')) {
					continue;
				}
				if ((ch >= 'A') && (ch <= 'F'))
				{
					continue;
				}
				cout << "Invalid Data !!!" << endl;
				return true;
			}
		}
		return false;
	}

	void processCommand()
	{
		Command* cmd;
		if (command == READ)
		{
			cmd = new ReadCmd(addr, nandIntf);
		}
		else if (command == WRITE) {
			cmd = new WriteCmd(addr, data, nandIntf);
		}
		else {
			cmd = new ErrorCmd(nandIntf);
		}
		cmd->run();
		delete cmd;
	}

	int getCmd() {
		return command;
	}
	int getAddr() {
		return addr;
	}
	string getData() {
		return data;
	}

private:
	NANDInterface* nandIntf;
	int command = 0;
	int addr = 0;
	string data;
	const int MIN_VALID_ARGUMENT_NUM = 3;
	const int VALID_READ_ARGUMENT_NUM = 3;
	const int VALID_WRITE_ARGUMENT_NUM = 4;
	const int MIN_LBA = 0;
	const int MAX_LBA = 99;
	const int DATA_LENGTH = 10;
};