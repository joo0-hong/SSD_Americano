#include "NandBuffer.h"
#include "CommandConverter.h"
#include "CommandOptimizer.h"

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
	COMMAND_ENTRY newCommand = { 'E', lba, size, ERASE_DATA };

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
	if (false == isValidSize(command)) {
		return;
	}

	updateCommandType(command);

	loadCommandBuffer();

	addCommandByOptimizing(command);

	storeCommandBuffer();
}

void NANDBuffer::addCommandByOptimizing(COMMAND_ENTRY command) {
	CommandOptimizer optimizer;

	optimizer.ignoreWrite1(commandBuffer, command);
	optimizer.ignoreWrite2(commandBuffer, command);
	optimizer.narrowRangeofErase(commandBuffer, command);
	optimizer.mergeErase(commandBuffer, command);

	commandBuffer.push_back(command);
}

void NANDBuffer::loadCommandBuffer() {
	CommandConverter converter;

	vector<string> commandsString = fileManager->readEntire();
	commandBuffer = converter.convertStringToCommands(commandsString);
}

void NANDBuffer::storeCommandBuffer() {
	CommandConverter converter;

	vector<string> commandsString = converter.convertCommandsToString(commandBuffer);
	fileManager->writeEntire(commandsString);
}

bool NANDBuffer::isValidSize(COMMAND_ENTRY& command)
{
	return (command.size > 0);
}

void NANDBuffer::updateCommandType(COMMAND_ENTRY& command)
{
	// Write lba 0x00000000 == Erase lba 1
	if ((command.cmdtype == COMMAND::WRITE) && (command.size == 1) && (command.data == ERASE_DATA)) {
		command.cmdtype = COMMAND::ERASE;
	}
}