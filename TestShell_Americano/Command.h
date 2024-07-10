#pragma once

enum class Command {
     WRITE = 0,
     READ = 1,
     EXIT = 2,
     HELP = 3,
     FULLWRITE = 4,
     FULLREAD = 5,
     ERASE = 6,
     ERASE_RANGE = 7,

    INVALID_COMMAND = -1,
    INVALID_ARGUMENT = -2
};