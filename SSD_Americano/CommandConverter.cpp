#include "CommandConverter.h"
#include <sstream>

vector<COMMAND_ENTRY> CommandConverter::convertStringToCommands(vector<string> stringCommands) {
	vector<COMMAND_ENTRY> commands = { };

	for (auto stringCommand : stringCommands) {
		COMMAND_ENTRY command = getCommandEntry(stringCommand);

		if (false == isCommandEntryValid(command)) {
			continue;
		}

		commands.push_back(command);
	}

	return commands;
}

vector<string> CommandConverter::convertCommandsToString(vector<COMMAND_ENTRY> commands) {
	vector<string> commandsInString;

	for (const auto& command : commands) {
		if (false == isCommandEntryValid(command)) {
			continue;
		}

		string stringCommand = getString(command);
		commandsInString.push_back(stringCommand);
	}

	return commandsInString;
}

COMMAND_ENTRY CommandConverter::getCommandEntry(string str) {
	vector<string> commandline = splitStringBySpaces(str);

	if (commandline.size() != 4) {
		return { };
	}
	if (commandline[0].size() != sizeof(COMMAND_ENTRY::cmdtype)) {
		return { };
	}

	COMMAND_ENTRY command = { };
	command.cmdtype = commandline[0][0];
	command.offset = stoi(commandline[1]);
	command.size = stoi(commandline[2]);
	command.data = commandline[3];

	return command;
}

string CommandConverter::getString(COMMAND_ENTRY entry) {
	string entryString = "";

	entryString += entry.cmdtype;
	entryString += ' ';
	entryString += to_string(entry.offset);
	entryString += ' ';
	entryString += to_string(entry.size);
	entryString += ' ';
	entryString += entry.data;

	return entryString;
}

vector<string> CommandConverter::splitStringBySpaces(const string& str) {
	vector<string> result;
	istringstream stream(str);
	string word;

	while (stream >> word) {
		result.push_back(word);
	}

	return result;
}

bool CommandConverter::isCommandEntryValid(COMMAND_ENTRY entry) {
	return ((COMMAND::WRITE == entry.cmdtype) || (COMMAND::ERASE == entry.cmdtype));
}
