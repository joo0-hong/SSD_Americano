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
        fstream file(filename, std::ios::in);

        checkFileOpen(file);

        data = readData(file, linenumber);

        file.close();

        return data;
    }

    void write(const int linenumber, const string& data) {
        vector<std::string> lines;
        fstream file(filename, std::ios::in | std::ios::out);

        checkFileOpen(file);

        writeData(file, linenumber, data);

        file.close();
    }

private:
    string filename;

    string readData(fstream& file, const int linenumber) {
        string line = "";
        streampos pos = getPosition(file, linenumber);

        file.seekg(pos);

        if (!getline(file, line)) {
            throw runtime_error("File status is not unstable");
        }

        return line;
    }

    void writeData(fstream& file, const int linenumber, const string& data) {
        streampos pos = getPosition(file, linenumber);

        file.seekp(pos);

        file << data;
    }

    streampos getPosition(fstream& file, const int linenumber) {
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

    void initFileDiscriptor(fstream& file) {
        file.clear();
        file.seekg(0);
        file.seekp(0);
    }

    void checkValidPosition(const streampos pos, const int curLinenumber, const int linenumber) {
        if ((-1 == pos) || (curLinenumber != linenumber)) {
            throw runtime_error("Invalid line number: " + linenumber);
        }
    }

    void checkFileOpen(fstream& file) {
        if (false == file.is_open()) {
            throw runtime_error("File can not be open.");
        }
    }
};