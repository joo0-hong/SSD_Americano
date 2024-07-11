#include "CommandOptimizer.h"

void CommandOptimizer::mergeErase(vector<COMMAND_ENTRY>& commandBuffer, COMMAND_ENTRY& newCommand) {
	if (newCommand.cmdtype == COMMAND::ERASE) {
		for (int i = commandBuffer.size() - 1; i >= 0; i--) {
			COMMAND_ENTRY& oldCommand = commandBuffer[i];

			if (oldCommand.cmdtype != COMMAND::ERASE) {
				continue;
			}

			if (false == isOverlap(newCommand, oldCommand)) {
				continue;
			}

			mergeEraseCommands(newCommand, oldCommand);
		}
	}
}

void CommandOptimizer::ignoreWrite2(vector<COMMAND_ENTRY>& commandBuffer, COMMAND_ENTRY& newCommand) {
	if (newCommand.cmdtype == COMMAND::ERASE) {
		for (int i = commandBuffer.size() - 1; i >= 0; i--) {
			COMMAND_ENTRY& oldCommand = commandBuffer[i];
			if (oldCommand.cmdtype != COMMAND::WRITE) {
				continue;
			}
			if (false == ((newCommand.offset <= oldCommand.offset) && (oldCommand.offset < newCommand.offset + newCommand.size))) {
				continue;
			}
			clearCommand(oldCommand);
		}
	}
}

void CommandOptimizer::ignoreWrite1(vector<COMMAND_ENTRY>& commandBuffer, COMMAND_ENTRY& newCommand) {
	if (newCommand.cmdtype != COMMAND::WRITE) {
		return;
	}

	for (int i = commandBuffer.size() - 1; i >= 0; i--) {
		COMMAND_ENTRY& oldCommand = commandBuffer[i];

		if (oldCommand.cmdtype != COMMAND::WRITE) {
			continue;
		}

		if (oldCommand.offset != newCommand.offset) {
			continue;
		}

		clearCommand(oldCommand);
	}
}

void CommandOptimizer::narrowRangeofErase(vector<COMMAND_ENTRY>& commandBuffer, COMMAND_ENTRY& newCommand)
{
	if (newCommand.cmdtype != COMMAND::WRITE) {
		return;
	}

	int startOffset = newCommand.offset;
	int endOffset = newCommand.offset + newCommand.size;

	for (int i = commandBuffer.size() - 1; i >= 0; i--) {
		COMMAND_ENTRY& oldCommand = commandBuffer[i];

		if (oldCommand.cmdtype == COMMAND::WRITE) {
			updateRange(startOffset, endOffset, oldCommand);
		}

		else if (oldCommand.cmdtype == COMMAND::ERASE) {
			removeFront(oldCommand, startOffset, endOffset);

			removeEnd(oldCommand, startOffset, endOffset);
		}
	}
}

void CommandOptimizer::removeFront(COMMAND_ENTRY& oldCommand, int startOffset, int endOffset)
{
	if ((startOffset <= oldCommand.offset) && (oldCommand.offset < endOffset)) {
		oldCommand.size -= (endOffset - oldCommand.offset);
		oldCommand.offset = endOffset;
	}

	if (oldCommand.size <= 0) {
		clearCommand(oldCommand);
	}
}

void CommandOptimizer::removeEnd(COMMAND_ENTRY& oldCommand, int startOffset, int endOffset)
{
	if ((startOffset <= oldCommand.offset + oldCommand.size - 1) &&
		(oldCommand.offset + oldCommand.size - 1 < endOffset)) {
		oldCommand.size -= (oldCommand.offset + oldCommand.size - startOffset);
	}

	if (oldCommand.size <= 0) {
		clearCommand(oldCommand);
	}
}

void CommandOptimizer::mergeEraseCommands(COMMAND_ENTRY& srcCommand, COMMAND_ENTRY& dstCommand) {
	int startOffset = min(dstCommand.offset, srcCommand.offset);
	int endOffset = max(dstCommand.offset + dstCommand.size, srcCommand.offset + srcCommand.size);

	dstCommand.offset = startOffset;
	dstCommand.size = endOffset - startOffset;
	clearCommand(srcCommand);
}

void CommandOptimizer::updateRange(int& startOffset, int& endOffset, const COMMAND_ENTRY& command) {
	if ((command.offset + 1 == startOffset) || (command.offset == endOffset)) {
		startOffset = min(startOffset, command.offset);
		endOffset = max(endOffset, command.offset + command.size);
	}
}

bool CommandOptimizer::isOverlap(COMMAND_ENTRY& newCommand, COMMAND_ENTRY& oldCommand) {
	return (((newCommand.offset <= oldCommand.offset + oldCommand.size)
		&& (oldCommand.offset <= newCommand.offset + newCommand.size)));
}

void CommandOptimizer::clearCommand(COMMAND_ENTRY& command) {
	command.cmdtype = COMMAND::INVALID;
}
