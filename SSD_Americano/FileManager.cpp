#include "FileManager.h"
#include <iostream>

string FileManager::read(const int linenumber) {
    vector<string> lines = { };

    checkInCapacity(linenumber);

    lines = getFileData();
    checkValidLinenumber(linenumber, lines.size());

    return lines[linenumber];
}

void FileManager::write(const int linenumber, const string& data) {
    vector<string> lines = { };

    checkInCapacity(linenumber);

    lines = getFileData();
    checkValidLinenumber(linenumber, lines.size());

    lines[linenumber] = data;

    setFileData(lines);
}

vector<string> FileManager::fullRead() {
    vector<string> lines = { };

    lines = getFileData();

    return lines;
}

void FileManager::fullWrite(const vector<string>& data) {
    setFileData(data);
}

vector<string> FileManager::getFileData() {
    fstream file(filename, ios::in);
    vector<string> lines = { };
    string line = "";

    checkFileOpen(file);

    while (getline(file, line)) {
        lines.push_back(line);
    }
    
    file.close();
    return lines;
}

void FileManager::setFileData(vector<string> lines) {
    fstream file(filename, ios::out);

    checkFileOpen(file);

    for (int i = 0; i < lines.size(); i++) {
        file << lines[i] << endl;
    }

    file.close();
}

void FileManager::checkFileOpen(fstream& file) {
    if (true == file.is_open()) {
        return;
    }

    throw runtime_error("File can not be open.");
}

void FileManager::checkInCapacity(const int linenumber) {
    if ((0 <= linenumber) && (linenumber <= MAX_LINENUMBER)) {
        return;
    }

    throw runtime_error("Invalid line number: " + linenumber);
}

void FileManager::checkValidLinenumber(const int linenumber, const int fileLinecount) {
    if (fileLinecount > linenumber) {
        return;
    }

    throw runtime_error("Invalid line number: " + linenumber);
}