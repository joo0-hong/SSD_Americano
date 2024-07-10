#pragma once
#include <string>

using namespace std;

class CommandBuffer {
public:
    CommandBuffer(string filename) : filename{ filename } { }

private:
    string filename;
};