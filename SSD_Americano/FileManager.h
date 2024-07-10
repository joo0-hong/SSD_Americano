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
    const int MAX_LINENUMBER = 99;
    string filename;

    vector<string> getFileData();
    void setFileData(vector<string> lines);
    void checkFileOpen(fstream& file);
    void checkInCapacity(const int linenumber);
    void checkValidLinenumber(const int linenumber, const int fileLinecount);
};