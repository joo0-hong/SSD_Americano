#include "FileManager.h"
#include <iostream>

string FileManager::read(const int linenumber) {
    string data = "";
    fstream file(filename, std::ios::in);

    checkFileOpen(file);

    data = readData(file, linenumber);

    file.close();

    return data;
}

void FileManager::write(const int linenumber, const string& data) {
    fstream file(filename, std::ios::in | std::ios::out);

    checkFileOpen(file);

    writeData(file, linenumber, data);

    file.close();
}

string FileManager::readData(fstream& file, const int linenumber) {
    vector<string> lines = { };

    lines = getFileData(file, linenumber, linenumber);

    if (1 != lines.size()) {
        throw runtime_error("Invalid line number: " + linenumber);
    }

    return lines[0];
}

void FileManager::writeData(fstream& file, const int linenumber, const string& data) {
    vector<string> lines = { };

    lines = getFileData(file, 0, 0x7FFFFFFF);

    if (lines.size() <= linenumber) {
        throw runtime_error("Invalid line number: " + linenumber);
    }

    lines[linenumber] = data;

    initFileDiscriptor(file);

    for (int i = 0; i < lines.size(); i++) {
        if (i + 1 < lines.size()) {
            file << lines[i] << endl;
        }
        else {
            file << lines[i];
        }
    }
}

void FileManager::writeResult(const int linenumber, const string& data) {
    fstream file(filename, std::ios::in | std::ios::out);

    initFileDiscriptor(file);
    file << data;

}

streampos FileManager::getPosition(fstream& file, const int linenumber) {
    int curLinenumber = 0;
    string line = "";

    initFileDiscriptor(file);

    while ((curLinenumber < linenumber) && (getline(file, line))) {
        curLinenumber++;
    }

    streampos pos = file.tellg();
    checkValidPosition(pos, curLinenumber, linenumber);

    return pos;
}

void FileManager::initFileDiscriptor(fstream& file) {
    file.clear();
    file.seekg(0);
    file.seekp(0);
}

vector<string> FileManager::getFileData(fstream& file, const int startLinenumber, const int endLinenumber) {
    vector<string> lines = { };
    string line = "";
    int curLinenumber = 0;

    initFileDiscriptor(file);

    while (getline(file, line)) {
        if ((startLinenumber <= curLinenumber) && (curLinenumber <= endLinenumber)) {
            lines.push_back(line);
        }

        curLinenumber++;
    }

    return lines;
}

void FileManager::checkValidPosition(const streampos pos, const int curLinenumber, const int linenumber) {
    if ((-1 == pos) || (curLinenumber != linenumber)) {
        throw runtime_error("Invalid line number: " + linenumber);
    }
}

void FileManager::checkFileOpen(fstream& file) {
    if (false == file.is_open()) {
        throw runtime_error("File can not be open.");
    }
}
