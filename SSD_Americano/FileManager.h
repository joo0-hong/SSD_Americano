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
    void writeResult(const int linenumber, const string& data);

private:
    const int MAX_LINENUMBER = 99;

    string filename;

    string readData(fstream& file, const int linenumber);
    void writeData(fstream& file, const int linenumber, const string& data);

    void checkValidLinenumber(const int linenumber);
    void checkFileOpen(fstream& file);

    vector<string> readFileData();
    void writeFileData(vector<string> lines);
};