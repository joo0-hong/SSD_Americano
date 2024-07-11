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

	vector<string> commandsString = getCommandsFromFile();

	vector<COMMAND_ENTRY> commands = convertStringToCommands(commandsString);

	commands.push_back(newCommand);

	optimize(commands);

	commandsString = convertCommandsToString(commands);

	addCommands(commandsString);
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

vector<string> NANDBuffer::getCommandsFromFile() {
	vector<string> commands = fileManager->readEntire();

	clearNull(commands);

	return commands;
}

void NANDBuffer::optimize(vector<COMMAND_ENTRY> commands) {

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

vector<COMMAND_ENTRY> NANDBuffer::convertStringToCommands(vector<string> stringCommands) {
	vector<COMMAND_ENTRY> commands = {};
	for (auto stringCommand : stringCommands) {
		vector<string> commandline = splitStringBySpaces(stringCommand);
		if (commandline.size() < 4) {
			throw runtime_error("invalid buffer size");
		}
		COMMAND_ENTRY command = {};
		if (commandline[0].size() != 1) throw runtime_error("1");

		command.cmdtype = commandline[0][0];
		command.offset = stoi(commandline[1]);
		command.size = stoi(commandline[2]);
		command.data = commandline[3];
		commands.push_back(command);
	}
	return commands;
}

vector<string> NANDBuffer::convertCommandsToString(vector<COMMAND_ENTRY> commands) {
	vector<string> commandsInString;
	for (const auto& command : commands) {
		string commandString = "";
		commandString += command.cmdtype;
		commandString += ' ';
		commandString += to_string(command.offset);
		commandString += ' ';
		commandString += to_string(command.size);
		commandString += ' ';
		commandString += command.data;

		commandsInString.push_back(commandString);
		;
	}
	return commandsInString;
}

void NANDBuffer::addCommands(vector<string> commandsString) {
	fileManager->writeEntire(commandsString);
}

void NANDBuffer::clearNull(vector<string>& commands) {
	auto new_end = remove(commands.begin(), commands.end(), "");
	commands.erase(new_end, commands.end());
}
