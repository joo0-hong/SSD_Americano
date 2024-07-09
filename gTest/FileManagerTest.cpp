#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD_Americano/FileManager.cpp"

#include <fstream>
#include <string>

using namespace testing;

class FileManagerTestFixture : public testing::Test {
protected:
    void SetUp() {
        fileManager = new FileManager(TESTFILENAME);
    }

    void writeFile(const string& filename, const vector<string>& data) {
        ofstream file(filename);

        if (file.is_open()) {
            for (const auto& line : data) {
                file << line << endl;
            }

            file.close();
        }
    }

    void verifyReadFileManager(const int linenumber, const string& expected) {
        string data_out = fileManager->read(linenumber);
        EXPECT_EQ(data_out, expected);
    }

    FileManager* fileManager;
    const string TESTFILENAME = "TestNand.txt";
};

TEST_F(FileManagerTestFixture, FileManager) {
    EXPECT_THAT(fileManager, NotNull());
}

TEST_F(FileManagerTestFixture, FileManagerRead) {
    int offset = 0;
    string data = "0x12341234";

    try {
        fileManager->read(offset);
    }
    catch (...) {
        FAIL();
    }
}

TEST_F(FileManagerTestFixture, FileManagerWrite) {
    int offset = 0;
    string data = "0x12341234";

    try {
        fileManager->write(offset, data);
    }
    catch (...) {
        FAIL();
    }
}

TEST_F(FileManagerTestFixture, FileManagerReadFileTest) {
    string data_out = "";
    vector<string> data = { "0x00000000", "0xFFFFFFFF" };

    writeFile(TESTFILENAME, data);

    verifyReadFileManager(0, data[0]);
    verifyReadFileManager(1, data[1]);
}
