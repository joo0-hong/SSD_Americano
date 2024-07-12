#pragma once
#include <string>

using namespace std;

namespace COMMAND {
	constexpr char ERASE = 'E';
	constexpr char WRITE = 'W';
	constexpr char INVALID = 0;
}

struct COMMAND_ENTRY {
	char cmdtype;
	int offset;
	int size;
	string data;
};