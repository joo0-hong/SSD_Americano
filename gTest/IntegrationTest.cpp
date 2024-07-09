#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD_Americano/HostInterface.cpp"
#include "../SSD_Americano/Nand.cpp"

#include <string>
#include <fstream>

using namespace std;
using namespace testing;

class IntegrationTest : public testing::Test {
protected:
    void SetUp() override {
        vector<string> data;
        for (int i = 0; i < MAX_FILE_LINE_COUNT; i++) {
            data.push_back(INITIAL_ZERO_STRING);
        }

        writeFile(TEST_NAND_FILE, data);
    }

    void processMain(int argc, char* argv[]) {
        hostIntf.processCommand(argc, argv);
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

TEST_F(IntegrationTest, ReadTest) {
    char* argument0 = "ssd";
    char* argument1 = "R";
    char* argument2 = "7";
    char* arguments[] = { argument0, argument1, argument2 };
    processMain(sizeof(arguments) / sizeof(char*), arguments);
}

TEST_F(IntegrationTest, WriteReadTest) {
    char* argumentsWrite[] = { "ssd", "W", "7", "0x77777777" };
    processMain(sizeof(argumentsWrite) / sizeof(char*), argumentsWrite);

    char* argumentsRead[] = { "ssd", "R", "7" };
    processMain(sizeof(argumentsRead) / sizeof(char*), argumentsRead);

    char* argumentsError[] = { "ssd", "error", "7" };
    processMain(sizeof(argumentsError) / sizeof(char*), argumentsError);
}
