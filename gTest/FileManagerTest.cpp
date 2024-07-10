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
        EXPECT_EQ(data_out, expected);
    }

    FileManager* fileManager;
    const string TESTFILENAME = "TestNand.txt";
    const string INITIAL_ZERO_STRING = "0x00000000";
    const int MAX_FILE_LINE_COUNT = 100;
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
    vector<string> data = { "0x00000000", "0xFFFFFFFF" };

    writeFile(TESTFILENAME, data);

    verifyReadFileManager(0, data[0]);
    verifyReadFileManager(1, data[1]);
}

TEST_F(FileManagerTestFixture, FileManagerAllZeroReadFileTest) {
    // Act & Assert
    for (int i = 0; i < MAX_FILE_LINE_COUNT; i++) {
        verifyReadFileManager(i, INITIAL_ZERO_STRING);
    }
}

TEST_F(FileManagerTestFixture, FileManagerWriteFileTest) {
    // Act
    fileManager->write(0, "0x12341234");
    fileManager->write(99, "0x43214321");

    // Assert
    for (int i = 1; i < 99; i++) {
        verifyReadFileManager(i, INITIAL_ZERO_STRING);
    }

    verifyReadFileManager(0, "0x12341234");
    verifyReadFileManager(99, "0x43214321");
}

TEST_F(FileManagerTestFixture, FileManagerWriteInvalidOffset) {
    // Act & Assert
    try {
        fileManager->write(MAX_FILE_LINE_COUNT, "0x12341234");
        FAIL();
    }
    catch (...) {
        // PASS
    }
}

TEST_F(FileManagerTestFixture, FileManagerWriteNegativeOffset) {
    // Act & Assert
    try {
        fileManager->write(-1, "0x12341234");
        FAIL();
    }
    catch (...) {
        // PASS
    }
}

TEST_F(FileManagerTestFixture, FileManagerReadNegativeOffset) {
    // Act & Assert
    try {
        fileManager->read(-1);
        FAIL();
    }
    catch (...) {
        // PASS
    }
}
TEST_F(FileManagerTestFixture, FileManagerReadInvalidOffset) {
    vector<string> data = { "0x00000000", "0xFFFFFFFF" };

    writeFile(TESTFILENAME, data);

    try {
        fileManager->read(data.size());
        FAIL();
    }
    catch (...) {
        // PASS
    }
}

TEST_F(FileManagerTestFixture, FileNotOpen) {
    FileManager* invalidFileManager = new FileManager("InvalidFilename");

    try {
        invalidFileManager->read(0);
        FAIL();
    }
    catch (...) {
        // PASS
    }
}
