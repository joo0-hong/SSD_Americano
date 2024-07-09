#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

class FileManager {
public:
    FileManager(const string& filename) : filename{ filename } { }

    string read(const int linenumber) {
        string data = "";
        fstream file(filename);

        checkFileOpen(file);

        checkLineNumberValid(file, linenumber);

        data = getLine(file, linenumber);

        file.close();

        return data;
    }

    void write(int linenumber, string data) {
        vector<std::string> lines;
        string line = "";
        fstream file(filename);

        checkFileOpen(file);

        checkLineNumberValid(file, linenumber);

        while (getline(file, line)) {
            lines.push_back(line);
        }

        lines[linenumber] = data;

        file.clear();
        file.seekg(0);

        for (const auto& l : lines) {
            file << l << std::endl;
        }

        file.close();
    }

private:
    string filename;

    string getLine(fstream& file, const int linenumber) {
        string line = "";
        int currentline = 0;

        file.seekg(0);

        while (getline(file, line)) {
            if (currentline == linenumber) {
                break;
            }
            currentline++;
        }

        return line;
    }

    void checkFileOpen(fstream& file) {
        if (false == file.is_open()) {

            throw runtime_error("File can not be open.");
        }
    }

    void checkLineNumberValid(fstream& file, const int linenumber) {
        int linecount = getLineCount(file);
        if (linenumber < 0) {
            throw runtime_error("Negative line number:" + linenumber);
        }
        if (linecount <= linenumber) {
            throw runtime_error("nand.txt does not have line: " + linenumber);
        }
    }

    int getLineCount(fstream& file) {
        string line = "";
        int currentline = 0;
        streampos currentPos = file.tellg();

        file.seekg(0);

        while (getline(file, line)) {
            currentline++;
        }

        file.clear();
        file.seekg(currentPos);

        return currentline;
    }
};