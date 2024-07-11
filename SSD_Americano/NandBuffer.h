#pragma once
#include <vector>
#include <sstream>
#include "FileManager.h"

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

	string read(const int lba);
	void write(const int lba, const string data);
	void erase(const int lba, const int size);
	vector<COMMAND_ENTRY> getCommands();
	int getCommandBufferSize();
	void clear();

private:
	const int MAX_BUFFER_SIZE = 10;

	const char ERASE = 'E';
	const char WRITE = 'W';
	const char INVALID = 0;

	FileManager* fileManager;
	vector<COMMAND_ENTRY> commandBuffer;

	void addCommand(COMMAND_ENTRY command);

	void loadCommandBuffer();
	void storeCommandBuffer();
	void addCommandByOptimizing(COMMAND_ENTRY command);

	void narrowRangeofErase(COMMAND_ENTRY& newCommand);
	void mergeErase(COMMAND_ENTRY& newCommand);
	void mergeEraseCommands(COMMAND_ENTRY& srcCommand, COMMAND_ENTRY& dstCommand);
	bool isOverlap(COMMAND_ENTRY& newCommand, COMMAND_ENTRY& oldCommand);
	void ignoreWrite2(COMMAND_ENTRY& newCommand);
	void ignoreWrite1(COMMAND_ENTRY& newCommand);
	void clearCommand(COMMAND_ENTRY& newCommand);

	vector<COMMAND_ENTRY> convertStringToCommands(vector<string> stringCommands);
	vector<string> convertCommandsToString(vector<COMMAND_ENTRY> commands);

	COMMAND_ENTRY getCommandEntry(string str);
	string getString(COMMAND_ENTRY entry);
	vector<string> splitStringBySpaces(const string& str);
	bool isCommandEntryValid(COMMAND_ENTRY entry);
};