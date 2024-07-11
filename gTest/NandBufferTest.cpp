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

TEST_F(NandBufferTestFixture, filemanagerReadWrite) {
    // Arrange
    vector<string> commands = { "test1", "test2"};

    // Act
    nandBuffer->addCommand(commands[0]);
    nandBuffer->addCommand(commands[1]);

    // Assert
    verifyResultFile(commands);
}
