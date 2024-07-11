#pragma once
#include "FileManager.h"
#include <vector>
#include <sstream>

using namespace std;

struct COMMAND_ENTRY {
	char cmdtype;
	int offset;
	int size;
	string data;
};

class NANDBuffer {
public:
	NANDBuffer(string bufferFile);
	~NANDBuffer();

	void read(const int lba);
	void write(const int lba, const string data);
	void erase(const int lba, const int size);
	vector<COMMAND_ENTRY> getCommands();
	int getCommandBufferSize();
	void clear();

private:
	const int MAX_BUFFER_SIZE = 10;
	FileManager* fileManager;

	vector<string> getCommandsFromFile();
	void optimize(vector<COMMAND_ENTRY> commands);
	vector<string> splitStringBySpaces(const string& str);
	vector<COMMAND_ENTRY> convertStringToCommands(vector<string> stringCommands);
	vector<string> convertCommandsToString(vector<COMMAND_ENTRY> commands);
	void addCommands(vector<string> commandsString);
	void clearNull(vector<string>& commands);
};