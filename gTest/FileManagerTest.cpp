#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD_Americano/FileManager.cpp"

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