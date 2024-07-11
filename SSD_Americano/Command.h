#pragma once
#define interface struct

interface Command {
	virtual ~Command() { }

	virtual void parse(int paramCount, char* param[]) = 0;
	virtual void run() = 0;
};
