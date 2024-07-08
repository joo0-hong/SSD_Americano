#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

class FileManager {
public:
    string read(int linenumber)
    {
        // TODO: Error handling of invalid linenumber
        ifstream openFile(filename);
        if (openFile.is_open()) {
            string line;
            int currentline = 0;

            while (getline(openFile, line)) {
                if (currentline == linenumber) {
                    return line;
                }
                currentline++;
            }
            openFile.close();
        }

        return "";
    }

    void write(int linenumber, string data)
    {
        return;
    }

private:
    const string filename = "nand.txt";
};