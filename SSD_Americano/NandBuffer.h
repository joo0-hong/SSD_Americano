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
	vector<COMMAND_ENTRY> commandBuffer;

	void loadCommands();
	void storeCommands();
	void optimizeCommands();

	vector<COMMAND_ENTRY> convertStringToCommands(vector<string> stringCommands);
	vector<string> convertCommandsToString(vector<COMMAND_ENTRY> commands);
	COMMAND_ENTRY getCommandEntry(string str);
	string getString(COMMAND_ENTRY entry);
	vector<string> splitStringBySpaces(const string& str);
	bool isCommandEntryValid(COMMAND_ENTRY entry);
};