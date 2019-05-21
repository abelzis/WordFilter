#include "gtest/gtest.h"
#include "../WordFilter/src/wordfilter.h"

namespace wordfilter
{
	typedef Text T;
	TEST(Constructor, Default)
	{
		T t;
		EXPECT_EQ(t.text(), "");
	}

	TEST(Constructor, StringParam)
	{
		T t{ "abA GaGa" };
		EXPECT_EQ(t.text(), "aba gaga");
	}

	TEST(Getter, Text)
	{
		T t{ "BBYYYaa3" };
		EXPECT_EQ(t.text(), "bbyyyaa3");
	}

	TEST(ReadFromFile, ReadText)
	{
		T t;
		std::ofstream b{ "kkee.txt" };
		b << "very nice STRIng it IS\n";
		b.close();
		ifstream c("kkee.txt");
		t.readFromFile(c);
		EXPECT_EQ(t.text(), "very nice string it is\n\n");
	}
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}