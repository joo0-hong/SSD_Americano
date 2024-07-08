#include <string>

using namespace std;

class TestShell {
public:
	void write(std::string lba, std::string data) {
		int lba_val = std::stoi(lba);
		if (lba_val < 0 || lba_val >= 100)
			throw;
	}
	void read(std::string lba) {
	}
	void exit() {
	}
	void help() {
	}
	void fullwrite() {
	}
	void fullread() {
	}
};