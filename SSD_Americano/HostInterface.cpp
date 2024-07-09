#include <iostream>
#include <string>
using namespace std;

static const int READ = 1;
static const int WRITE = 2;

class HostInterface {
public:
	void ParseCommand(int argc, char* argv[]) {
		if (checkInvalidCommand(argc, argv)) {
			return;
		}

		if (string(argv[1]) == "W") {
			command = WRITE;
			data = string(argv[3]);
		}
		else if (string(argv[1]) == "R") {
			command = READ;
		}
		else {
			cout << "ERROR" << endl;
		}

		addr = atoi(argv[2]);
	}

	bool checkInvalidCommand(int argc, char* argv[]) {

		if (string(argv[1]) != "R" && string(argv[1]) != "W") {
			return true;
		}

		if (argc < MIN_VALID_ARGUMENT_NUM) {
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
				cout << "Invalid Data: Data should start with 0x !!! " << dataPreFix<< endl;
				return true;
			}
		}

		return false;
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