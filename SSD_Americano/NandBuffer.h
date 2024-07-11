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

	void read(const int lba) {
		
	}

	void write(const int lba, const string data) {

	}

	void erase(const int lba, const int size) {

	}

	vector<string> getCommands() {
		return { };
	}

	vector<string> getCommandsFromFile() {
		return fileManager->fullRead();
	}

	void addCommand(string commandLine) {
		vector<string> commands = getCommandsFromFile();
		commands.push_back(commandLine);

		clearNull(commands);

		fileManager->fullWrite(commands);
	}

private:
	const int MAX_BUFFER_SIZE = 10;

	FileManager* fileManager;

	void clearNull(vector<string>& commands) {
		auto new_end = remove(commands.begin(), commands.end(), "");
		commands.erase(new_end, commands.end());
	}
};