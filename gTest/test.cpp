#include "gtest/gtest.h"
#include "gmock/gmock.h"

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
