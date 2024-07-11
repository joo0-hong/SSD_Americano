#pragma once
#include "CommandTypes.h"
#include <vector>
#include <string>

using namespace std;

class CommandConverter {
public:
	vector<COMMAND_ENTRY> convertStringToCommands(vector<string> stringCommands);
	vector<string> convertCommandsToString(vector<COMMAND_ENTRY> commands);

private:
	COMMAND_ENTRY getCommandEntry(string str);
	string getString(COMMAND_ENTRY entry);
	vector<string> splitStringBySpaces(const string& str);
	bool isCommandEntryValid(COMMAND_ENTRY entry);
};