#pragma once
#define interface struct

interface Command {
	virtual ~Command() { }
	virtual void run() = 0;
};