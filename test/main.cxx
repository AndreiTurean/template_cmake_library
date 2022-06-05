#include <iostream>
#include <source.hpp>
#include <gtest/gtest.h>
 
TEST(add, positive_numbers) 
{ 
    EXPECT_EQ(src::add(1,1),2);
}

TEST(add, negative_numbers)
{
    EXPECT_EQ(src::add(-1,-2),-3);
}

TEST(subtract, negative_numbers)
{
    EXPECT_EQ(src::subtract(-1,-2),1);
}

TEST(subtract, positive_numbers)
{
    EXPECT_EQ(src::subtract(1,2),-1);
}

TEST(multiply, positive_numbers)
{
    EXPECT_EQ(src::multiply(1,2),2);
}
TEST(multiply, negative_numbers)
{
    EXPECT_EQ(src::multiply(-1,-2),2);
}

TEST(divide, non_zero)
{
    EXPECT_EQ(src::divide(4,2),2);
}

TEST(divide, zero)
{
    EXPECT_EQ(src::divide(4,0),0);
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}