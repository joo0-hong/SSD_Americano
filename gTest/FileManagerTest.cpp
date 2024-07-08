#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD_Americano/FileManager.cpp"

#include <fstream>

using namespace testing;

class FileManagerTestFixture : public testing::Test {
protected:
    void SetUp() {
        fileManager = new FileManager();
    }

    FileManager* fileManager;
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
    string word_offset0 = "0x00000000";
    string word_offset1 = "0xFFFFFFFF";
    string testFileName = "nand.txt";
    string data_out = "";

    ofstream testFile(testFileName);
    if (testFile.is_open()) {
        testFile << word_offset0 << endl;
        testFile << word_offset1 << endl;
    }

    data_out = fileManager->read(0);
    EXPECT_EQ(word_offset0, data_out);

    data_out = fileManager->read(1);
    EXPECT_EQ(word_offset1, data_out);
}
