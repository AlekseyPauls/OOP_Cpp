#include "gtest/gtest.h"
#include "mytrit.h"


TEST(testTritSet, MemoryTest)
{
	trit_set::TritSet set(1000);
	size_t alloc_length = set.capacity();
	EXPECT_GE(alloc_length, 1000 * 2 / 8 / sizeof(uint));
	set[1000000000] = trit_set::Unknown;
	EXPECT_EQ(alloc_length, set.capacity());
	if (set[2000000000] == trit_set::True) {}
	EXPECT_EQ(alloc_length, set.capacity());
	set[1000000000] = trit_set::True;
	EXPECT_LT(alloc_length, set.capacity());
	alloc_length = set.capacity();
	set[1000000000] = trit_set::Unknown;
	set[1000000] = trit_set::False;
	EXPECT_EQ(alloc_length, set.capacity());
	set.shrink();
	EXPECT_GT(alloc_length, set.capacity());
	set.trim(100);
	EXPECT_EQ(100, set.capacity());
}

TEST(testTritSet, OperationsTest) {
	trit_set::TritSet setA(1000);
	trit_set::TritSet setB(2000);
	trit_set::TritSet setC = setA & setB;
	EXPECT_EQ(setC.capacity(), setB.capacity());
	setC.trim(0);
	setC = setA | setB;
	EXPECT_EQ(setC.capacity(), setB.capacity());
	setC = ~setA;
	EXPECT_EQ(setC.capacity(), setA.capacity());
}

TEST(testTritSet, FunctionTest) {
	trit_set::TritSet set(1000);
	for (int i = 0; i < 100; i++)
	{
		set[i] = trit_set::True;
	}
	size_t length = set.length();
	EXPECT_EQ(length, 100);
	size_t trits_number = set.cardinality(trit_set::True);
	EXPECT_EQ(trits_number, 100);
	set[500] = trit_set::False;
	std::unordered_map< trit_set::Trit, size_t, std::hash<int> > m = set.cardinality();
	EXPECT_EQ(m[trit_set::True], 100);
	EXPECT_EQ(m[trit_set::False], 1);
	EXPECT_EQ(m[trit_set::Unknown], 1000 - 100 - 1);
}