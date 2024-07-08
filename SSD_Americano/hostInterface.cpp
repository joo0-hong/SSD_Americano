#include <iostream>
#include <string>
using namespace std;

static const int READ = 1;
static const int WRITE = 2;

class HostInterface {
public:
	void ParseCommand(int argc, char* argv[]) {
		if (*argv[1] == 'W') {
			command = WRITE;
			data = *((int*)argv[3]);
		}
		else if (*argv[1] == 'R') {
			command = READ;
		}
		else {
			cout << "ERROR" << endl;
		}

		addr = *((int*)argv[2]);
	}

	int getCmd() {
		return command;
	}
	int getAddr() {
		return addr;
	}
	int getData() {
		return data;
	}

private:
	int command = 0;
	int addr = 0;
	int data = 0;
};