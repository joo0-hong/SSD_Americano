#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD_Americano/NandDriver.h"
#include "../SSD_Americano/NAND.h"
#include "../SSD_Americano/FileManager.h"

#include <fstream>
#include <string>

using namespace testing;


class NandDriverTestFixture : public testing::Test {
protected:
    void SetUp() {
        fileManager = new FileManager(TESTFILENAME);
        nand = new NAND{ TESTFILENAME, TESTRESULTFILE };
        nandBuffer = new NANDBuffer{ TESTBUFFERFILE };
        nandDriver = new NANDDriver(nand, nandBuffer);

        vector<string> data;
        for (int i = 0; i < MAX_FILE_LINE_COUNT; i++) {
            data.push_back(INITIAL_ZERO_STRING);
        }

        writeFile(TESTFILENAME, data);
    }

    void writeFile(const string& filename, const vector<string>& data) {
        ofstream file(filename);

        if (false == file.is_open()) {
            FAIL();
        }

        for (int i = 0; i < data.size(); i++) {
            if (i == data.size() - 1) {
                file << data[i];
            }
            else {
                file << data[i] << endl;
            }
        }

        file.close();
    }

    void verifyReadFileManager(const int linenumber, const string& expected) {
        string data_out = fileManager->read(linenumber);
        EXPECT_THAT(data_out, Eq(expected));
    }

    NANDDriver* nandDriver;
    FileManager* fileManager;
    NAND* nand;
    NANDBuffer* nandBuffer;

    const string TESTFILENAME = "TestNand.txt";
    const string TESTRESULTFILE = "TestResult.txt";
    const string TESTBUFFERFILE = "TestResult.txt";
    const string INITIAL_ZERO_STRING = "0x00000000";
    const int MAX_FILE_LINE_COUNT = 100;
};

