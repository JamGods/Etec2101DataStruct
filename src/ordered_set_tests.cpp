// ordered_set_tests.cpp
#include <gtest/gtest.h>
#include <ordered_set.h>

using namespace ssuds;

TEST(OrderedSetTests, InsertAndContains)
{
    OrderedSet<int> set;
    EXPECT_FALSE(set.contains(10));
    set.insert(10);
    EXPECT_TRUE(set.contains(10));
    set.insert(5);
    set.insert(15);
    EXPECT_TRUE(set.contains(5));
    EXPECT_TRUE(set.contains(15));
}

TEST(OrderedSetTests, SizeAndClear)
{
    OrderedSet<int> set;
    EXPECT_EQ(set.size(), 0);
    set.insert(10);
    set.insert(5);
    set.insert(15);
    EXPECT_EQ(set.size(), 3);
    set.clear();
    EXPECT_EQ(set.size(), 0);
}

TEST(OrderedSetTests, GetHeight)
{
    OrderedSet<int> set;
    set.insert(10);
    set.insert(5);
    set.insert(15);
    set.insert(3);
    EXPECT_EQ(set.get_height(), 3);
}

TEST(OrderedSetTests, Traversal)
{
    OrderedSet<int> set;
    set.insert(10);
    set.insert(5);
    set.insert(15);
    auto in_order = set.traversal(Traversal::IN_ORDER);
    EXPECT_EQ(in_order.size(), 3);
    EXPECT_EQ(in_order[0], 5);
    EXPECT_EQ(in_order[1], 10);
    EXPECT_EQ(in_order[2], 15);
}

TEST(OrderedSetTests, Rebalance)
{
    OrderedSet<int> set;
    for (int i = 1; i <= 7; ++i)
        set.insert(i);
    EXPECT_EQ(set.get_height(), 7); // Skewed tree
    set.rebalance();
    EXPECT_EQ(set.get_height(), 3); // Balanced tree
}

TEST(OrderedSetTests, GetParent)
{
    OrderedSet<int> set;
    set.insert(10);
    set.insert(5);
    set.insert(15);
    set.insert(3);
    set.insert(7);

    auto parent_of_3 = set.get_parent(3);
    ASSERT_TRUE(parent_of_3.has_value());
    EXPECT_EQ(parent_of_3.value(), 5);

    auto parent_of_10 = set.get_parent(10);
    EXPECT_FALSE(parent_of_10.has_value()); // Root
}
