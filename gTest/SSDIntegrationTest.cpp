#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD_Americano/HostInterface.cpp"
#include "../SSD_Americano/Nand.cpp"

#include <vector>
#include <string>
#include <fstream>

using namespace std;
using namespace testing;

class SSDIntegrationTest : public testing::Test {
protected:
    void SetUp() override {
        vector<string> data;
        for (int i = 0; i < MAX_FILE_LINE_COUNT; i++) {
            data.push_back(INITIAL_ZERO_STRING);
        }

        writeFile(TEST_NAND_FILE, data);
        writeFile(TEST_RESULT_FILE, { "" });
    }

    void processMain(int argc, char* argv[]) {
        hostIntf.processCommand(argc, argv);
    }

    void verifyFile(const string& filename, const vector<string>& expected) {
        ifstream file(filename);
        string line = "";
        vector<string> lines;

        if (false == file.is_open()) {
            FAIL();
        }

        while (getline(file, line)) {
            lines.push_back(line);
        }

        EXPECT_EQ(expected.size(), lines.size());

        for (int i = 0; i < lines.size(); i++) {
            EXPECT_EQ(lines[i], expected[i]);
        }

        file.close();
    }

    const string TEST_NAND_FILE = "TestNand.txt";
    const string TEST_RESULT_FILE = "TestResult.txt";
    const string INITIAL_ZERO_STRING = "0x00000000";
    const int MAX_FILE_LINE_COUNT = 100;

    NAND nand{ TEST_NAND_FILE, TEST_RESULT_FILE };
    HostInterface hostIntf{ &nand };

private:
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
};

TEST_F(SSDIntegrationTest, ReadTest) {
    char* arguments[] = { "ssd", "R", "1" };
    processMain(sizeof(arguments) / sizeof(char*), arguments);

    verifyFile(TEST_RESULT_FILE, { "0x00000000" });
}

TEST_F(SSDIntegrationTest, WriteReadTest) {
    char* argumentsWrite[] = { "ssd", "W", "7", "0x77777777" };
    processMain(sizeof(argumentsWrite) / sizeof(char*), argumentsWrite);

    char* argumentsRead[] = { "ssd", "R", "7" };
    processMain(sizeof(argumentsRead) / sizeof(char*), argumentsRead);

    verifyFile(TEST_RESULT_FILE, { "0x77777777" });
}
TEST_F(SSDIntegrationTest, InvalidCommandTest) {
    char* argumentsError[] = { "ssd", "T", "7" };
    processMain(sizeof(argumentsError) / sizeof(char*), argumentsError);

    verifyFile(TEST_RESULT_FILE, { "NULL" });
}
