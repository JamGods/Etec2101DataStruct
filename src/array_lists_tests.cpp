#include <gtest/gtest.h>
#include <array_list.h>

using namespace ssuds;

TEST(ArrayListTest, ConstructorTest) {
    ArrayList<int> list;
    EXPECT_EQ(list.size(), 0);
}

TEST(ArrayListTest, AppendAndSizeTest) {
    ArrayList<int> list;
    list.append(10);
    list.append(20);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], 10);
    EXPECT_EQ(list[1], 20);
}

TEST(ArrayListTest, OutOfBoundsAccess) {
    ArrayList<int> list;
    list.append(5);
    EXPECT_THROW(list[1], std::out_of_range);
}

TEST(ArrayListTest, FindTest) {
    ArrayList<int> list = { 1, 2, 3, 4, 5 };
    auto it = list.find(3);
    EXPECT_NE(it, list.end());
    EXPECT_EQ(*it, 3);
}

TEST(ArrayListTest, RemoveTest) {
    ArrayList<int> list = { 1, 2, 3, 4, 5 };
    list.remove(3);
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list.find(3), list.end());
}

TEST(ArrayListTest, IterationTest) {
    ArrayList<int> list = { 10, 20, 30 };
    int sum = 0;
    for (int val : list) {
        sum += val;
    }
    EXPECT_EQ(sum, 60);
}