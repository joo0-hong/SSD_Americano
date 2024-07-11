#include "CommandCommon.h"

void CommandCommon::checkLBAValid(char* param)
{
	if (false == isNumber(string(param))) {
		throw invalid_argument("Invalid LBA");
	}

	if (false == isInRange(atoi(param), MIN_LBA, MAX_LBA)) {
		throw invalid_argument("LBA is out of range");
	}
}

bool CommandCommon::isNumber(const string param) {
	for (const char ch : param) {
		if (('0' <= ch) && (ch <= '9')) {
			continue;
		}
		return false;
	}
	return true;
}

bool CommandCommon::isInRange(const int number, const int start, const int end) {
	if ((start <= number) && (number <= end)) {
		return true;
	}
	return false;
}
