#include "NandBuffer.h"

NANDBuffer::NANDBuffer(string bufferFile) {
	fileManager = new FileManager{ bufferFile };
}

NANDBuffer::~NANDBuffer() {
	if (nullptr != fileManager) {
		delete fileManager;
	}
}

string NANDBuffer::read(const int lba) {
	loadCommandBuffer();

	for (int i = commandBuffer.size() - 1; i >= 0; i--) {
		COMMAND_ENTRY& cmd = commandBuffer[i];
		if ((cmd.offset <= lba) && (lba < cmd.offset + cmd.size)) {
			return cmd.data;
		}
	}

	return "";
}

void NANDBuffer::write(const int lba, const string data) {
	COMMAND_ENTRY newCommand = { 'W', lba, 1, data };

	addCommand(newCommand);
}

void NANDBuffer::erase(const int lba, const int size) {
	COMMAND_ENTRY newCommand = { 'E', lba, size, "0x00000000" };

	addCommand(newCommand);
}

vector<COMMAND_ENTRY> NANDBuffer::getCommands() {
	loadCommandBuffer();

	return commandBuffer;
}

int NANDBuffer::getCommandBufferSize() {
	loadCommandBuffer();

	return commandBuffer.size();
}

void NANDBuffer::clear() {
	commandBuffer.clear();

	storeCommandBuffer();
}

void NANDBuffer::addCommand(COMMAND_ENTRY command) {
	loadCommandBuffer();

	commandBuffer.push_back(command);

	optimizeCommands();

	storeCommandBuffer();
}

void NANDBuffer::optimizeCommands() {

}

void NANDBuffer::loadCommandBuffer() {
	vector<string> commandsString = fileManager->readEntire();
	commandBuffer = convertStringToCommands(commandsString);
}

void NANDBuffer::storeCommandBuffer() {
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