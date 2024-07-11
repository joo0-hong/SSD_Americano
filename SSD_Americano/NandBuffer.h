#pragma once
#include "FileManager.h"
#include <vector>

using namespace std;

class NANDBuffer {
public:
	NANDBuffer(string bufferFile) {
		fileManager = new FileManager{ bufferFile };
	}
	~NANDBuffer() {
		if (nullptr != fileManager) {
			delete fileManager;
		}
	}

	void read(int lba) {
		
	}

	void write(int lba, string data) {

	}

	void erase(int lba, int size) {

	}

	vector<string> getCommands() {
		return { };
	}

private:
	const int MAX_BUFFER_SIZE = 10;

	FileManager* fileManager;
};