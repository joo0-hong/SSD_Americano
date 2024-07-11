#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSD_Americano/HostInterface.cpp"
#include "../SSD_Americano/Nand.cpp"
#include "../SSD_Americano/FileManager.cpp"
#include "../SSD_Americano/CommandCommon.cpp"
#include "../SSD_Americano/EraseCmd.cpp"
#include "../SSD_Americano/WriteCmd.cpp"
#include "../SSD_Americano/ReadCmd.cpp"
#include "../SSD_Americano/FlushCmd.cpp"
#include "../SSD_Americano/ErrorCmd.cpp"

#include <vector>
#include <string>
#include <fstream>

using namespace std;
using namespace testing;

class SSDIntegrationTest : public testing::Test {
protected:
    void SetUp() override {
        vector<string> data;
        for (int i = 0; i < MAX_FILE_LINE_COUNT; i++) {
            data.push_back(INITIAL_ZERO_STRING);
        }

        writeFile(TEST_NAND_FILE, data);
        writeFile(TEST_RESULT_FILE, { "\n" });
    }

    void mainRead(const int linenumber) {
        char arg[11] = { };
        itoa(linenumber, arg, 10);

        char* arguments[] = { "ssd", "R", arg };

        main(sizeof(arguments) / sizeof(char*), arguments);
    }

    void mainWrite(const int linenumber, const string data) {
        char arg[11] = { };
        itoa(linenumber, arg, 10);

        char* arguments[] = { "ssd", "W", arg, (char*)data.c_str()};

        main(sizeof(arguments) / sizeof(char*), arguments);
    }

    void main(const int argc, char* argv[]) {
        hostIntf.processCommand(argc, argv);
    }

    void verifyResultFile(const vector<string>& expected) {
        ifstream file(TEST_RESULT_FILE);
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

    const string TEST_NAND_FILE = "TestNand.txt";
    const string TEST_RESULT_FILE = "TestResult.txt";
    const string INITIAL_ZERO_STRING = "0x00000000";
    const int MAX_FILE_LINE_COUNT = 100;

    NAND nand{ TEST_NAND_FILE, TEST_RESULT_FILE };
    HostInterface hostIntf{ &nand };

private:
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

TEST_F(SSDIntegrationTest, ReadTest) {
    // Arrange: 0x00000000

    // Act
    mainRead(1);

    // Assert
    verifyResultFile({ "0x00000000" });
}

TEST_F(SSDIntegrationTest, WriteReadTest) {
    // Arrange
    int linenumber = 7;
    string data = "0x77777777";

    // Act
    mainWrite(linenumber, data);

    // Assert
    mainRead(linenumber);
    verifyResultFile({ data });
}

TEST_F(SSDIntegrationTest, NoArgumentTest) {
    char* invalidArgument[] = { "ssd" };

    // Act
    main(sizeof(invalidArgument) / sizeof(char*), invalidArgument);

    // Assert
    verifyResultFile({ "NULL" });
}

TEST_F(SSDIntegrationTest, InvalidCommandTest) {
    // Arrange
    char* invalidArgument[] = { "ssd", "T", "7" };

    // Act
    main(sizeof(invalidArgument) / sizeof(char*), invalidArgument);

    // Assert
    verifyResultFile({ "NULL" });
}

TEST_F(SSDIntegrationTest, InvalidReadArguments) {
    // Arrange
    char* invalidArgument[] = { "ssd", "R", "7", "7" };

    // Act
    main(sizeof(invalidArgument) / sizeof(char*), invalidArgument);

    // Assert
    verifyResultFile({ "NULL" });
}

TEST_F(SSDIntegrationTest, InvalidReadLBA) {
    // Arrange
    char* invalidArgument[] = { "ssd", "R", "7A" };

    // Act
    main(sizeof(invalidArgument) / sizeof(char*), invalidArgument);

    // Assert
    verifyResultFile({ "NULL" });
}

TEST_F(SSDIntegrationTest, InvalidReadLBARange) {
    // Arrange
    char* invalidArgument[] = { "ssd", "R", "100" };

    // Act
    main(sizeof(invalidArgument) / sizeof(char*), invalidArgument);

    // Assert
    verifyResultFile({ "NULL" });
}

TEST_F(SSDIntegrationTest, InvalidWriteArguments) {
    // Arrange
    char* invalidArgument[] = { "ssd", "W", "7"};

    // Act
    main(sizeof(invalidArgument) / sizeof(char*), invalidArgument);

    // Assert
    verifyResultFile({ "NULL" });
}

TEST_F(SSDIntegrationTest, InvalidWriteLinenumber) {
    // Arrange
    char* invalidArgument[] = { "ssd", "W", "7B", "0xABCDABCD"};

    // Act
    main(sizeof(invalidArgument) / sizeof(char*), invalidArgument);

    // Assert
    verifyResultFile({ "NULL" });
}

TEST_F(SSDIntegrationTest, InvalidWriteDataLength) {
    // Arrange
    char* invalidArgument[] = { "ssd", "W", "7", "0xABCDABCDA" };

    // Act
    main(sizeof(invalidArgument) / sizeof(char*), invalidArgument);

    // Assert
    verifyResultFile({ "NULL" });
}

TEST_F(SSDIntegrationTest, InvalidWriteDataNoPrefix_0x) {
    // Arrange
    char* invalidArgument[] = { "ssd", "W", "7", "ABCDABCDAB" };

    // Act
    main(sizeof(invalidArgument) / sizeof(char*), invalidArgument);

    // Assert
    verifyResultFile({ "NULL" });
}

TEST_F(SSDIntegrationTest, InvalidEraseLBA) {
    // Arrange
    char* invalidArgument[] = { "ssd", "E", "7A", "10"};

    // Act
    main(sizeof(invalidArgument) / sizeof(char*), invalidArgument);

    // Assert
    verifyResultFile({ "NULL" });
}

TEST_F(SSDIntegrationTest, InvalidEraseLBARange) {
    // Arrange
    char* invalidArgument[] = { "ssd", "E", "100", "10" };

    // Act
    main(sizeof(invalidArgument) / sizeof(char*), invalidArgument);

    // Assert
    verifyResultFile({ "NULL" });
}

TEST_F(SSDIntegrationTest, InvalidEraseSize) {
    // Arrange
    char* invalidArgument[] = { "ssd", "E", "0", "11" };

    // Act
    main(sizeof(invalidArgument) / sizeof(char*), invalidArgument);

    // Assert
    verifyResultFile({ "NULL" });
}

TEST_F(SSDIntegrationTest, InvalidEraseSize0) {
    // Arrange
    char* invalidArgument[] = { "ssd", "E", "0", "0" };

    // Act (Do nothing)
    main(sizeof(invalidArgument) / sizeof(char*), invalidArgument);

    // Assert
    verifyResultFile({ "" });
}
