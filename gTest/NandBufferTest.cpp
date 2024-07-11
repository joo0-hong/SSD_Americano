#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD_Americano/NandBuffer.h"
#include "../SSD_Americano/FileManager.h"

using namespace std;
using namespace testing;

class NandBufferTestFixture : public testing::Test {
public:
    void SetUp() override {
        nandBuffer = new NANDBuffer(TEST_BUFFER_FILENAME);

        writeFile(TEST_BUFFER_FILENAME, { "\n" });
    }
    void TearDown() override{
        if (nullptr != nandBuffer) {
            delete nandBuffer;
        }
    }

    void verifyResultFile(const vector<string>& expected) {
        ifstream file(TEST_BUFFER_FILENAME);
        string line = "";
        vector<string> lines;

        if (false == file.is_open()) {
            FAIL();
        }

        while (getline(file, line)) {
            lines.push_back(line);
        }

        EXPECT_EQ(expected.size(), lines.size());

        for (int i = 0; i < lines.size(); i++) {
            EXPECT_THAT(lines[i], Eq(expected[i]));
        }

        file.close();
    }

protected:
    NANDBuffer* nandBuffer;
    const string TEST_BUFFER_FILENAME = "TestBuffer.txt";

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

TEST_F(NandBufferTestFixture, createAPI) {
    vector<string> comp = { };

    nandBuffer->read(0);
    nandBuffer->write(0, "0x00000000");
    nandBuffer->erase(0, 10);
    EXPECT_THAT(comp, ContainerEq(nandBuffer->getCommands()));
}

TEST_F(NandBufferTestFixture, WriteFunction) {
    // Arrange
    vector<string> commands = { "W 0 1 0x12341234"};

    // Act
    nandBuffer->write(0, "0x12341234");

    // Assert
    verifyResultFile(commands);
}

TEST_F(NandBufferTestFixture, WriteFunctionTwice) {
    // Arrange
    vector<string> commands = { "W 0 1 0x12341234", "W 5 1 0xFFFFFFFF" };

    // Act
    nandBuffer->write(0, "0x12341234");
    nandBuffer->write(5, "0xFFFFFFFF");

    // Assert
    verifyResultFile(commands);
}
