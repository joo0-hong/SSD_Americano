#include <string>
#include <iostream>

using namespace std;

class TestShell {
public:
	TestShell(const std::string& ssd_path, const std::string& result_path)
		: SSD_PATH(ssd_path), RESULT_PATH(result_path) {}

	void write(std::string lba, std::string data) {
		string cmd("W");
		string ret = SSD_PATH + " " + cmd + " " + lba + " " + data;
		system(ret.c_str());
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

private:
	string SSD_PATH;
	string RESULT_PATH;
};