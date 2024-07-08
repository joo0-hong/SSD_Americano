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
