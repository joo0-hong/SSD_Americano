#pragma once
#include "CommandTypes.h"
#include <string>
#include <vector>

using namespace std;


class CommandOptimizer {
public:
	void mergeErase(vector<COMMAND_ENTRY>& commandBuffer, COMMAND_ENTRY& newCommand);
	void ignoreWrite2(vector<COMMAND_ENTRY>& commandBuffer, COMMAND_ENTRY& newCommand);
	void ignoreWrite1(vector<COMMAND_ENTRY>& commandBuffer, COMMAND_ENTRY& newCommand);
	void narrowRangeofErase(vector<COMMAND_ENTRY>& commandBuffer, COMMAND_ENTRY& newCommand);

protected:
	void mergeEraseCommands(COMMAND_ENTRY& srcCommand, COMMAND_ENTRY& dstCommand);
	void updateRange(int& startOffset, int& endOffset, const COMMAND_ENTRY& command);
	void removeFront(COMMAND_ENTRY& oldCommand, int startOffset, int endOffset);
	void removeEnd(COMMAND_ENTRY& oldCommand, int startOffset, int endOffset);
	bool isOverlap(COMMAND_ENTRY& newCommand, COMMAND_ENTRY& oldCommand);
	void clearCommand(COMMAND_ENTRY& newCommand);
};