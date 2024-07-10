#pragma once
#include "WriteCmd.h"
#include "EraseCmd.h"
#include "ReadCmd.h"
#include "ErrorCmd.h"

class CommandFactory {
public:
    static Command* getNewCommand(const string& command, NANDInterface* nand) {
        if ("R" == command) {
            return new ReadCmd(nand);
        }
        if ("W" == command) {
            return new WriteCmd(nand);
        }
        if ("E" == command) {
            return new EraseCmd(nand);
        }

        throw invalid_argument("This command is not available.");
    }
};