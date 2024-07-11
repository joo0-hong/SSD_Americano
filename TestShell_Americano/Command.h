#pragma once

enum class Command {
    
    WRITE = 0,
    READ = 1,
    EXIT = 2,
    HELP = 3,
    FULLWRITE = 4,
    FULLREAD = 5,
    TESTAPP1 = 6,
    TESTAPP2 = 7,
    ERASE = 8,
    ERASE_RANGE = 9,
    FLUSH = 10,
    SCENARIO = 11,

    INVALID_COMMAND = -1,
    INVALID_ARGUMENT = -2
};