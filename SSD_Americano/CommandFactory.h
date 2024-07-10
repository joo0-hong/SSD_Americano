#pragma once
#include "WriteCmd.h"
#include "EraseCmd.h"
#include "ReadCmd.h"
#include "ErrorCmd.h"

class CommandFactory {
public:
    static Command* newCommand(const string& command, NANDInterface* nand) {
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

    static Command* newErrorCommand(NANDInterface* nand) {
        return new ErrorCmd(nand);
    }
};