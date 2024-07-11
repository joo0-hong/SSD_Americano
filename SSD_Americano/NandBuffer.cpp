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
	for (int i = commandBuffer.size() - 1; i >= 0; i--) {
		COMMAND_ENTRY& cmd = commandBuffer[i];

		if (cmd.cmdtype == 'W') {
			for (int j = i - 1; j >= 0; j--) {
				if (i == j) {
					continue;
				}
				if (commandBuffer[j].cmdtype != 'W') {
					continue;
				}
				if (commandBuffer[j].offset != cmd.offset) {
					continue;
				}
				commandBuffer[j].cmdtype = 0;
			}
		}

		if (cmd.cmdtype == 'E') {
			for (int j = i - 1; j >= 0; j--) {
				if (i == j) {
					continue;
				}
				if (commandBuffer[j].cmdtype != 'W') {
					continue;
				}
				if (false == ((cmd.offset <= commandBuffer[j].offset) && (commandBuffer[j].offset < cmd.offset + cmd.size))) {
					continue;
				}
				commandBuffer[j].cmdtype = 0;
			}

			for (int j = i - 1; j >= 0; j--) {
				if (i == j) {
					continue;
				}
				if (commandBuffer[j].cmdtype != 'E') {
					continue;
				}

				if (false == 
					(((cmd.offset <= commandBuffer[j].offset + commandBuffer[j].size) 
					&& (commandBuffer[j].offset <= cmd.offset + cmd.size)))) {
					continue;
				}

				int start_offset = min(cmd.offset, commandBuffer[j].offset);
				int end_offset = max(cmd.offset + cmd.size, commandBuffer[j].offset + commandBuffer[j].size);

				bool continueFlag = false;
				for (int k = j + 1; k < i; k++) {
					if ((commandBuffer[k].cmdtype == 'W') &&
						((start_offset <= commandBuffer[k].offset) && (commandBuffer[k].offset < end_offset))) {
						continueFlag = true;
					}
				}
				if (continueFlag) {
					continue;
				}

				cmd.offset = start_offset;
				cmd.size = end_offset - start_offset;

				commandBuffer[j].cmdtype = 0;
			}

		}
	}
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
