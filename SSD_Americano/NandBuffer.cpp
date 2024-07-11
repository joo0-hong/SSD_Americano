#include "NandBuffer.h"

NANDBuffer::NANDBuffer(string bufferFile) {
	fileManager = new FileManager{ bufferFile };
}

NANDBuffer::~NANDBuffer() {
	if (nullptr != fileManager) {
		delete fileManager;
	}
}

void NANDBuffer::read(const int lba) {

}

void NANDBuffer::write(const int lba, const string data) {
	COMMAND_ENTRY newCommand = { 'W', lba, 1, data };
	loadCommands();

	commandBuffer.push_back(newCommand);

	optimizeCommands();

	storeCommands();
}

void NANDBuffer::erase(const int lba, const int size) {

}

vector<COMMAND_ENTRY> NANDBuffer::getCommands() {
	return { };
}

int NANDBuffer::getCommandBufferSize() {
	return 0;
}

void NANDBuffer::clear() {

}

void NANDBuffer::optimizeCommands() {

}

void NANDBuffer::loadCommands() {
	vector<string> commandsString = fileManager->readEntire();
	commandBuffer = convertStringToCommands(commandsString);
}

void NANDBuffer::storeCommands() {
	vector<string> commandsString = convertCommandsToString(commandBuffer);
	fileManager->writeEntire(commandsString);
}

vector<COMMAND_ENTRY> NANDBuffer::convertStringToCommands(vector<string> stringCommands) {
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

vector<string> NANDBuffer::convertCommandsToString(vector<COMMAND_ENTRY> commands) {
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

COMMAND_ENTRY NANDBuffer::getCommandEntry(string str) {
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

string NANDBuffer::getString(COMMAND_ENTRY entry) {
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

vector<string> NANDBuffer::splitStringBySpaces(const string& str) {
	vector<string> result;
	istringstream stream(str);
	string word;

	while (stream >> word) {
		result.push_back(word);
	}

	return result;
}

bool NANDBuffer::isCommandEntryValid(COMMAND_ENTRY entry) {
	return (('W' == entry.cmdtype) || ('E' == entry.cmdtype));
}
