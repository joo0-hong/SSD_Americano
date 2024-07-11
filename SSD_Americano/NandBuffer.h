#pragma once
#include "CommandOptimizer.h"
#include <vector>
#include "FileManager.h"

using namespace std;

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
	string ERASE_DATA = "0x00000000";

	FileManager* fileManager;
	vector<COMMAND_ENTRY> commandBuffer;

	void loadCommandBuffer();
	void storeCommandBuffer();

	void addCommand(COMMAND_ENTRY command);
	void updateCommandType(COMMAND_ENTRY& command);
	bool isValidSize(COMMAND_ENTRY& command);
	void addCommandByOptimizing(COMMAND_ENTRY command);
};