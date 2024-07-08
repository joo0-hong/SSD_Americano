#include <iostream>
#include <fstream>
#include <string>

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
		invokeSSDRead(lba);

		std::cout << getSSDReadData() << std::endl;
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
	const std::string SSD_PATH;
	const std::string RESULT_PATH;

	void invokeSSDRead(std::string& lba)
	{
		string cmd("R");
		std::string ret = SSD_PATH + " " + cmd + " " + lba;
		system(ret.c_str());
	}
	std::string getSSDReadData() {
		std::string result;

		std::ifstream ifs;
		ifs.open(RESULT_PATH);
		ifs >> result;
		ifs.close();

		return result;
	}
};