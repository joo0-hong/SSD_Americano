#include "FileManager.h"
#include <iostream>

string FileManager::read(const int linenumber) {
    string data = "";
    fstream file(filename, std::ios::in);

    checkFileOpen(file);

    checkValidLinenumber(linenumber);

    data = readData(file, linenumber);

    file.close();

    return data;
}

void FileManager::write(const int linenumber, const string& data) {
    fstream file(filename, std::ios::in | std::ios::out);

    checkFileOpen(file);

    checkValidLinenumber(linenumber);

    writeData(file, linenumber, data);

    file.close();
}

string FileManager::readData(fstream& file, const int linenumber) {
    vector<string> lines = { };

    lines = readFileData();

    if (lines.size() <= linenumber) {
        throw runtime_error("Invalid line number: " + linenumber);
    }

    return lines[linenumber];
}

void FileManager::writeData(fstream& file, const int linenumber, const string& data) {
    vector<string> lines = { };

    lines = readFileData();

    if (lines.size() <= linenumber) {
        throw runtime_error("Invalid line number: " + linenumber);
    }

    lines[linenumber] = data;

    writeFileData(lines);
}

void FileManager::writeResult(const int linenumber, const string& data) {
    fstream file(filename, std::ios::out);

    file << data;

    file.close();
}

void FileManager::checkFileOpen(fstream& file) {
    if (true == file.is_open()) {
        return;
    }

    throw runtime_error("File can not be open.");
}

vector<string> FileManager::readFileData() {
    ifstream file(filename);
    vector<string> lines = { };
    string line = "";

    if (false == file.is_open()) {
        throw runtime_error("File can not be open.");
    }

    while (getline(file, line)) {
        lines.push_back(line);
    }
    
    file.close();
    return lines;
}

void FileManager::writeFileData(vector<string> lines) {
    ofstream file(filename);

    if (false == file.is_open()) {
        throw runtime_error("File can not be open.");
    }

    for (int i = 0; i < lines.size(); i++) {
        file << lines[i] << endl;
    }

    file.close();
}

void FileManager::checkValidLinenumber(const int linenumber) {
    if ((0 <= linenumber) && (linenumber <= MAX_LINENUMBER)) {
        return;
    }

    throw runtime_error("Invalid line number: " + linenumber);
}