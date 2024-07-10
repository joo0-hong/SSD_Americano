#pragma once

#include <string>
#include <fstream>
#include <vector>

using namespace std;

class FileManager {
public:
    FileManager(const string& filename) : filename{ filename } { }
    string read(const int linenumber);
    void write(const int linenumber, const string& data);

private:
    string filename;

    string readData(fstream& file, const int linenumber);
    void writeData(fstream& file, const int linenumber, const string& data);

    streampos getPosition(fstream& file, const int linenumber);
    void initFileDiscriptor(fstream& file);
    void checkValidPosition(const streampos pos, const int curLinenumber, const int linenumber);
    void checkFileOpen(fstream& file);
};