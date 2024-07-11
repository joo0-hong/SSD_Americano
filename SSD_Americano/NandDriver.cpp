#include <iostream>
#include "NandDriver.h"
#include "Nand.h"

void NANDDriver::read(const int lba) {
	string result = nandBuffer->read(lba);
	if (result == "") {
		nand->read(lba);
		return;
	}
	
	nand->writeResult(result);
}

void NANDDriver::write(const int lba, const string data) {
	if (nandBuffer->getCommandBufferSize() >= MAX_BUFFER_NUM) {
		flush();
	}
	nandBuffer->write(lba, data);
}

void NANDDriver::erase(const int lba, const int size) {
	if (nandBuffer->getCommandBufferSize() >= MAX_BUFFER_NUM) {
		flush();
	}
	nandBuffer->erase(lba, size);
}

void NANDDriver::error(void) {
	nand->error();
}

void NANDDriver::flush() {
	vector<COMMAND_ENTRY> cmdListInBuffer = nandBuffer->getCommands();
	for(auto cmd : cmdListInBuffer) {
		if (cmd.cmdtype == 'W') {
			nand->write(cmd.offset, cmd.data);
			continue;
		} 		
		if (cmd.cmdtype == 'E') {
			nand->erase(cmd.offset, cmd.size);
		}
	}

	nandBuffer->clear();
}