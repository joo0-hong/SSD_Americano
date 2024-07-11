#pragma once
#include <string>
#include <stdexcept>
#include "Command.h"
#include "NandInterface.h"
#include "NandDriver.h"

using namespace std;

class CommandCommon : public Command {
public:
	virtual void parse(int paramCount, char* param[]) = 0;
	virtual void run() = 0;

protected:
	const int MAX_LBA = 99;
	const int MIN_LBA = 0;

	void checkLBAValid(char* param);
	bool isNumber(const string param);
	bool isInRange(const int number, const int start, const int end);
};