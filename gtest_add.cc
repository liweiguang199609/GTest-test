#include <gtest/gtest.h>

extern int add(int a, int b);

TEST(testCase, test0)
{
    EXPECT_EQ(add(2, 3), 5);
}

TEST(testCase, test1)
{
    EXPECT_EQ(add(4, 3), 7);
}