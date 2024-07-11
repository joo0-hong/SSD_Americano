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
	NANDBuffer(string bufferFile) {
		fileManager = new FileManager{ bufferFile };
	}
	~NANDBuffer() {
		if (nullptr != fileManager) {
			delete fileManager;
		}
	}

	void read(const int lba) {
		
	}

	void write(const int lba, const string data) {
		COMMAND_ENTRY newCommand = { 'W', lba, 1, data };

		vector<string> commandsString = getCommandsFromFile();

		vector<COMMAND_ENTRY> commands = convertStringToCommands(commandsString);

		commands.push_back(newCommand);

		optimize(commands);

		commandsString = convertCommandsToString(commands);
		
		addCommands(commandsString);
	}

	void erase(const int lba, const int size) {

	}

	vector<string> getCommands() {
		return { };
	}

	vector<string> getCommandsFromFile() {
		vector<string> commands = fileManager->fullRead();

		clearNull(commands);

		return commands;
	}

	void optimize(vector<COMMAND_ENTRY> commands) {

	}

	vector<string> splitStringBySpaces(const string& str) {
		vector<string> result;
		istringstream stream(str);
		string word;

		while (stream >> word) {
			result.push_back(word);
		}

		return result;
	}

	vector<COMMAND_ENTRY> convertStringToCommands(vector<string> stringCommands) {
		vector<COMMAND_ENTRY> commands = { };
		for (auto stringCommand : stringCommands) {
			vector<string> commandline = splitStringBySpaces(stringCommand);
			if (commandline.size() < 4) {
				throw runtime_error("invalid buffer size");
			}
			COMMAND_ENTRY command = { };
			if (commandline[0].size() != 1) throw runtime_error("1");

			command.cmdtype = commandline[0][0];
			command.offset = stoi(commandline[1]);
			command.size = stoi(commandline[2]);
			command.data = commandline[3];
			commands.push_back(command);
		}
		return commands;
	}

	vector<string> convertCommandsToString(vector<COMMAND_ENTRY> commands) {
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
;		}
		return commandsInString;
	}

	void addCommands(vector<string> commandsString) {
		fileManager->fullWrite(commandsString);
	}

private:
	const int MAX_BUFFER_SIZE = 10;

	FileManager* fileManager;

	void clearNull(vector<string>& commands) {
		auto new_end = remove(commands.begin(), commands.end(), "");
		commands.erase(new_end, commands.end());
	}
};