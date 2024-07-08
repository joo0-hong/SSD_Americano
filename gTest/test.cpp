#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD_Americano/NandInterface.h"
#include "../SSD_Americano/FileManager.cpp"

using namespace testing;

class MockedNand : public NANDInterface {
public:
    MOCK_METHOD(void, read, (int lba), (override));
    MOCK_METHOD(void, write, (int lba, int data), (override));
};

TEST(SSDTest, NANDInterface) {
    MockedNand nand;

    EXPECT_CALL(nand, read(_)).Times(1);
    EXPECT_CALL(nand, write(_, _)).Times(1);

    nand.read(0);
    nand.write(0, 0);
}

TEST(FileManagerTest, FileManager) {
    FileManager* fileManager = new FileManager();

    EXPECT_THAT(fileManager, NotNull());
}

TEST(FileManagerTest, FileManagerRead) {
    FileManager* fileManager = new FileManager();
    int offset = 0;
    string data = "0x12341234";

    try {
        fileManager->read(offset);
    }
    catch (...) {
        FAIL();
    }
}

TEST(FileManagerTest, FileManagerWrite) {
    FileManager* fileManager = new FileManager();
    int offset = 0;
    string data = "0x12341234";

    try {
        fileManager->write(offset, data);
    }
    catch (...) {
        FAIL();
    }

}