#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

class FileManager {
public:
    FileManager(const string& filename) {
        file.open(filename);
        checkFileOpen();
    }
    ~FileManager() {
        file.close();
    }

    string read(const int linenumber) {
        // TODO: Error handling of invalid linenumber

        checkFileOpen();

        file.seekg(0);

        string line = getLine(linenumber);

        return line;
    }

    void write(int linenumber, string data) {
        return;
    }

private:
    string filename;
    fstream file;

    string getLine(const int linenumber) {
        string line = "";
        int currentline = 0;

        while (getline(file, line)) {
            if (currentline == linenumber) {
                return line;
            }
            currentline++;
        }
        return line;
    }

    void checkFileOpen() {
        if (false == file.is_open()) {

            throw runtime_error("File can not be open.");
        }
    }
};