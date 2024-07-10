#include "HostInterface.h"
#include "ErrorCmd.h"
#include "WriteCmd.h"
#include "ReadCmd.h"
#include "EraseCmd.h"

void HostInterface::processCommand(int argc, char* argv[])
{
	Command* cmd = nullptr;
	bool isInvalidCmd = checkInvalidCommand(argc, argv);

	if (isInvalidCmd == true) {
		cmd = new ErrorCmd(nandIntf);
	}
	else if (string(argv[1]) == "W") {
		addr = atoi(argv[2]);
		data = string(argv[3]);
		cmd = new WriteCmd(addr, data, nandIntf);
	}
	else if (string(argv[1]) == "R") {
		addr = atoi(argv[2]);
		cmd = new ReadCmd(addr, nandIntf);
	}
	else if (string(argv[1]) == "E") {
		addr = atoi(argv[2]);
		size = string(argv[3]);
		cmd = new EraseCmd(addr, size, nandIntf);
	}

	cmd->run();
	delete cmd;
}

bool HostInterface::checkInvalidCommand(int argc, char* argv[]) {
	if (checkInvalidArguementNumber(argc, argv)) {
		return true;
	}

	if (checkInvalidLBA(argv)) {
		return true;
	}

	if (checkInvalidDataToWrite(argv)) {
		return true;
	}

	if (checkEraseSize(argv)) {
		return true;
	}

	return false;
}

bool HostInterface::checkInvalidArguementNumber(int argc, char* argv[])
{
	if (argc < MIN_VALID_ARGUMENT_NUM) {
		return true;
	}

	if (string(argv[1]) != "R" && string(argv[1]) != "W" && string(argv[1]) != "E") {
		return true;
	}

	if (string(argv[1]) == "R" && argc != VALID_READ_ARGUMENT_NUM) {
		return true;
	}

	if (string(argv[1]) == "W" && argc != VALID_WRITE_ARGUMENT_NUM) {
		return true;
	}

	if (string(argv[1]) == "E" && argc != VALID_ERASE_ARGUMENT_NUM) {
		return true;
	}

	return false;
}

bool HostInterface::checkInvalidLBA(char* argv[])
{
	if (string(argv[1]) == "R" || string(argv[1]) == "W" || string(argv[1]) == "E") {
		for (const char ch : string(argv[2])) {
			if ((ch >= '0') && (ch <= '9')) {
				continue;
			}
			cout << "Invalid LBA !!!" << endl;
			return true;
		}
		int lba = atoi(argv[2]);
		if (lba < MIN_LBA || lba > MAX_LBA) {
			cout << "LBA is out of range !!!" << endl;
			return true;
		}
	}

	return false;
}


bool HostInterface::checkInvalidDataToWrite(char* argv[])
{
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

bool HostInterface::checkEraseSize(char* argv[])
{
	if (string(argv[1]) == "E") {
		for (const char ch : string(argv[3])) {
			if ((ch >= '0') && (ch <= '9')) {
				continue;
			}
			cout << "Invalid erase size !!!" << endl;
			return true;
		}

		int eraseSize = stoi(string(argv[3]));
		if (eraseSize <= 0 && eraseSize > MAX_ERASE_SIZE) {
			cout << "Invalid erase size !!!" << endl;
			return true;
		}
	}

	return false;
}

inline int HostInterface::getCmd() {
	return command;
}

inline int HostInterface::getAddr() {
	return addr;
}

inline string HostInterface::getData() {
	return data;
}
