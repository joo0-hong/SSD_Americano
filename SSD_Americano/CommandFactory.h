#pragma once
#include "WriteCmd.h"
#include "EraseCmd.h"
#include "ReadCmd.h"
#include "FlushCmd.h"
#include "ErrorCmd.h"

class CommandFactory {
public:
    static Command* newCommand(const string& command, NANDDriver* nandDriver) {
        if ("R" == command) {
            return new ReadCmd(nandDriver);
        }
        if ("W" == command) {
            return new WriteCmd(nandDriver);
        }
        if ("E" == command) {
            return new EraseCmd(nandDriver);
        }
        if ("F" == command) {
            return new FlushCmd(nandDriver);
        }

        throw invalid_argument("This command is not available.");
    }

    static Command* newErrorCommand(NANDDriver* nand) {
        return new ErrorCmd(nand);
    }
};