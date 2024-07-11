#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD_Americano/NandBuffer.h"
#include "../SSD_Americano/FileManager.h"

using namespace std;
using namespace testing;

class NandBufferTestFixture : public testing::Test {
public:
    void SetUp() override {
        nandBuffer = new NANDBuffer(TESTFILENAME);
    }
    void TearDown() override{
        if (nullptr != nandBuffer) {
            delete nandBuffer;
        }
    }
protected:
    NANDBuffer* nandBuffer;
    const string TESTFILENAME = "TestBuffer.txt";
};

TEST_F(NandBufferTestFixture, createAPI) {
    vector<string> comp = { };

    nandBuffer->read(0);
    nandBuffer->write(0, "0x00000000");
    nandBuffer->erase(0, 10);
    EXPECT_THAT(comp, ContainerEq(nandBuffer->getCommands()));
}
