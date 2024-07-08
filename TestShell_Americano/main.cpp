#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <string>

//namespace fs = std::filesystem;

using std::string;
using std::cin;

int main() {
	string cmd, data, LBA;

	system("cd");
	//fs::path current_path = fs::current_path();


	while (true) {
		cin >> cmd >> LBA >> data;
		string ret = "..\\x64\\Debug\\SSDMock " + cmd + " " + LBA + " " + data;

		
		system(ret.c_str());
	}

}