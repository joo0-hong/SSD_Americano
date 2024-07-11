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
    vector<COMMAND_ENTRY> comp = { };

    nandBuffer->read(0);
    nandBuffer->write(0, "0x00000000");
    nandBuffer->erase(0, 10);
    nandBuffer->getCommands();
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

TEST_F(NandBufferTestFixture, WriteFunctionInitialFile) {
    // Arrange
    writeFile(TEST_BUFFER_FILENAME, { });
    vector<string> commands = { "W 0 1 0x12341234"};

    // Act
    nandBuffer->write(0, "0x12341234");

    // Assert
    verifyResultFile(commands);
}

TEST_F(NandBufferTestFixture, EraseFunction) {
    // Arrange
    vector<string> commands = { "E 0 10 0x00000000" };

    // Act
    nandBuffer->erase(0, 10);

    // Assert
    verifyResultFile(commands);
}

TEST_F(NandBufferTestFixture, EraseFunctionTwice) {
    // Arrange
    vector<string> commands = { "E 0 10 0x00000000", "E 30 10 0x00000000" };

    // Act
    nandBuffer->erase(0, 10);
    nandBuffer->erase(30, 10);

    // Assert
    verifyResultFile(commands);
}

TEST_F(NandBufferTestFixture, WriteEraseBasic) {
    // Arrange
    vector<string> commands = {
        "W 14 1 0xFFFFFFFF", 
        "E 0 10 0x00000000",
        "W 99 1 0xFFFFFFFF",
        "E 30 10 0x00000000",
    };

    // Act
    nandBuffer->write(14, "0xFFFFFFFF");
    nandBuffer->erase(0, 10);
    nandBuffer->write(99, "0xFFFFFFFF");
    nandBuffer->erase(30, 10);

    // Assert
    verifyResultFile(commands);
}

TEST_F(NandBufferTestFixture, InitialRead) {
    EXPECT_THAT(string(""), Eq(nandBuffer->read(0)));
}

TEST_F(NandBufferTestFixture, GetCommands) {
    // Arrange
    vector<COMMAND_ENTRY> expected = {
        {'W', 14, 1,  "0xFFFFFFFF"},
        {'E', 0,  10, "0x00000000"},
        {'W', 99, 1,  "0xFFFFFFFF"},
        {'E', 30, 10, "0x00000000"},
    };

    // Act
    nandBuffer->write(14, "0xFFFFFFFF");
    nandBuffer->erase(0, 10);
    nandBuffer->write(99, "0xFFFFFFFF");
    nandBuffer->erase(30, 10);

    // Assert
    EXPECT_EQ(4, nandBuffer->getCommandBufferSize());
    vector<COMMAND_ENTRY> actual = nandBuffer->getCommands();

    EXPECT_EQ(expected.size(), actual.size());
    for (int i = 0; i < expected.size(); i++) {
        EXPECT_EQ(actual[i].cmdtype, expected[i].cmdtype);
        EXPECT_EQ(actual[i].offset, expected[i].offset);
        EXPECT_EQ(actual[i].size, expected[i].size);
        EXPECT_THAT(actual[i].data, Eq(expected[i].data));
    }
}

TEST_F(NandBufferTestFixture, Clear) {
    // Arrange
    vector<string> commands = {
        "W 14 1 0xFFFFFFFF",
        "E 0 10 0x00000000",
        "W 99 1 0xFFFFFFFF",
        "E 30 10 0x00000000",
    };

    nandBuffer->write(14, "0xFFFFFFFF");
    nandBuffer->erase(0, 10);
    nandBuffer->write(99, "0xFFFFFFFF");
    nandBuffer->erase(30, 10);

    verifyResultFile(commands);

    // Act
    nandBuffer->clear();

    // Assert
    verifyResultFile({ });
}

TEST_F(NandBufferTestFixture, ReadBasic) {
    // Arrange
    vector<string> commands = {
        "W 14 1 0xFFFFFFFF",
        "E 0 10 0x00000000",
        "W 99 1 0xFFFFFFFF",
        "E 30 10 0x00000000",
    };

    nandBuffer->write(14, "0xFFFFFFFF");
    nandBuffer->erase(0, 10);
    nandBuffer->write(99, "0xFFFFFFFF");
    nandBuffer->erase(30, 10);

    // Act & Assert
    EXPECT_EQ(string("0xFFFFFFFF"), nandBuffer->read(14));
    EXPECT_EQ(string("0x00000000"), nandBuffer->read(9));
    EXPECT_EQ(string(""), nandBuffer->read(10));
    EXPECT_EQ(string("0xFFFFFFFF"), nandBuffer->read(99));
    EXPECT_EQ(string("0x00000000"), nandBuffer->read(30));
}

TEST_F(NandBufferTestFixture, AlgorithmSameLBAWrite) {
    // Arrange
    vector<string> commands = {
        "W 23 1 0x77777777",
    };

    // Act
    nandBuffer->write(23, "0xFFFFFFFF");
    nandBuffer->write(23, "0x77777777");

    // Assert
    verifyResultFile(commands);
}

TEST_F(NandBufferTestFixture, AlgorithmEraseIncludingPreviousLBA) {
    // Arrange
    vector<string> commands = {
        "E 23 1 0x00000000",
    };

    // Act
    nandBuffer->write(23, "0xFFFFFFFF");
    nandBuffer->erase(23, 1);

    // Assert
    verifyResultFile(commands);
}

TEST_F(NandBufferTestFixture, AlgorithmEraseNotIncludingPreviousLBA) {
    // Arrange
    vector<string> commands = {
        "W 23 1 0x77777777",
        "E 20 3 0x00000000",
    };

    // Act
    nandBuffer->write(23, "0x77777777");
    nandBuffer->erase(20, 3);

    // Assert
    verifyResultFile(commands);
}

TEST_F(NandBufferTestFixture, AlgorithmEraseIncludingErase) {
    // Arrange
    vector<string> commands = {
        "E 20 10 0x00000000",
    };

    // Act
    nandBuffer->erase(20, 5);
    nandBuffer->erase(20, 10);

    // Assert
    verifyResultFile(commands);
}

TEST_F(NandBufferTestFixture, AlgorithmEraseOverlapErase) {
    // Arrange
    vector<string> commands = {
        "E 15 15 0x00000000",
    };

    // Act
    nandBuffer->erase(15, 10);
    nandBuffer->erase(20, 10);

    // Assert
    verifyResultFile(commands);
}

TEST_F(NandBufferTestFixture, AlgorithmEraseBridgeErase) {
    // Arrange
    vector<string> commands = {
        "E 10 20 0x00000000",
    };

    // Act
    nandBuffer->erase(10, 10);
    nandBuffer->erase(20, 10);

    // Assert
    verifyResultFile(commands);
}

TEST_F(NandBufferTestFixture, AlgorithmWriteBetweenErase) {
    // Arrange
    vector<string> commands = {
        "W 10 1 0x77777777",
        "E 11 19 0x00000000",
    };

    // Act
    nandBuffer->erase(10, 10);
    nandBuffer->write(10, "0x77777777");
    nandBuffer->erase(20, 10);

    // Assert
    verifyResultFile(commands);
}

TEST_F(NandBufferTestFixture, AlgorithmMergeWriteBetweenErase) {
    // Arrange
    vector<string> commands = {
        "E 10 20 0x00000000",
    };

    // Act
    nandBuffer->erase(10, 10);
    nandBuffer->write(20, "0x77777777");
    nandBuffer->erase(20, 10);

    // Assert
    verifyResultFile(commands);
}

TEST_F(NandBufferTestFixture, AlgorithmWriteEdgeOfErase) {
    // Arrange
    vector<string> commands = {
        "E 10 2 0x00000000",
        "E 40 5 0x00000000",
        "W 12 1 0xABCD1234",
        "W 13 1 0x4BCD5351",
    };

    // Act
    nandBuffer->erase(10, 4);
    nandBuffer->erase(40, 5);
    nandBuffer->write(12, "0xABCD1234");
    nandBuffer->write(13, "0x4BCD5351");

    // Assert
    verifyResultFile(commands);
}

TEST_F(NandBufferTestFixture, AlgorithmWriteEdgeOfEraseAndDeleteErase) {
    // Arrange
    vector<string> commands = {
        "E 40 5 0x00000000",
        "W 50 1 0xABCD1234",
    };

    // Act
    nandBuffer->erase(50, 1);
    nandBuffer->erase(40, 5);
    nandBuffer->write(50, "0xABCD1234");

    // Assert
    verifyResultFile(commands);
}

TEST_F(NandBufferTestFixture, AlgorithmComplex) {
    // Arrange
    vector<string> commands = {
        "E 46 10 0x00000000",
        "W 47 1 0xABCD1234",
        "W 48 1 0xABCD1234",
        "W 49 1 0xABCD1234",
        "W 50 1 0xABCD1234",
        "W 46 1 0xABCD1234",
    };

    // Act
    nandBuffer->erase(46, 10);
    nandBuffer->write(47, "0xABCD1234");
    nandBuffer->write(48, "0xABCD1234");
    nandBuffer->write(49, "0xABCD1234");
    nandBuffer->write(50, "0xABCD1234");
    nandBuffer->write(46, "0xABCD1234");

    // Assert
    verifyResultFile(commands);
}