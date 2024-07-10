#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD_Americano/CommandBuffer.h"

using namespace testing;

class CommandBufferTestFixture : public testing::Test {
protected:
    void SetUp() override {
        commandBuffer = new CommandBuffer(TEST_FILE_NAME);
    }

    const string TEST_FILE_NAME = "TestCommandBuffer";
    CommandBuffer* commandBuffer;
};

TEST_F(CommandBufferTestFixture, CommandBufferConstructor) {
    EXPECT_THAT(commandBuffer, NotNull());
}