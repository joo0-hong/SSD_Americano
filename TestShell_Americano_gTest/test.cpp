#include "gmock/gmock.h"
#include "../TestShell_Americano/TestShell.cpp"
#include <string>

using namespace std;


TEST(TestShell, TestShellWriteFail_LBA_largerThan100) {
	TestShell ts;

	string lba("100");
	string data("0x1298CDEF");

	ts.write(lba, data);

	EXPECT_THROW(
		{ ts.write(lba, data); }
		,std::exception());
}

TEST(TestShell, TestShellWriteFail_LBA_lessThan0) {
	TestShell ts;

	string lba("-1");
	string data("0x1298CDEF");

	ts.write(lba, data);

	EXPECT_THROW(
		{ ts.write(lba, data); }
	, std::exception());
}
