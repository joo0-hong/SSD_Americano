#pragma once
#include "Command.h"
#include "NandInterface.h"

class ErrorCmd : public Command {
public:
	ErrorCmd(NANDInterface* nand) : nandIntf(nand) {
	}
	void run() override {
		nandIntf->error();
	}

private:
	NANDInterface* nandIntf;
};