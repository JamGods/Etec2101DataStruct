#include <gtest/gtest.h>
#include <array_list.h>

using namespace ssuds;

TEST(ArrayOperationsTest, CopyConstructorTest) {
    ArrayList<int> list = { 1, 2, 3 };
    ArrayList<int> copyList(list);
    EXPECT_EQ(copyList.size(), 3);
    EXPECT_EQ(copyList[0], 1);
    EXPECT_EQ(copyList[1], 2);
    EXPECT_EQ(copyList[2], 3);
}

TEST(ArrayOperationsTest, MoveConstructorTest) {
    ArrayList<int> list = { 5, 10, 15 };
    ArrayList<int> movedList(std::move(list));
    EXPECT_EQ(movedList.size(), 3);
    EXPECT_EQ(movedList[0], 5);
    EXPECT_EQ(movedList[1], 10);
    EXPECT_EQ(movedList[2], 15);
}

TEST(ArrayOperationsTest, AssignmentOperatorTest) {
    ArrayList<int> list = { 7, 8, 9 };
    ArrayList<int> assignedList;
    assignedList = list;
    EXPECT_EQ(assignedList.size(), 3);
    EXPECT_EQ(assignedList[0], 7);
    EXPECT_EQ(assignedList[1], 8);
    EXPECT_EQ(assignedList[2], 9);
}

TEST(ArrayOperationsTest, MoveAssignmentOperatorTest) {
    ArrayList<int> list = { 100, 200, 300 };
    ArrayList<int> assignedList;
    assignedList = std::move(list);
    EXPECT_EQ(assignedList.size(), 3);
    EXPECT_EQ(assignedList[0], 100);
    EXPECT_EQ(assignedList[1], 200);
    EXPECT_EQ(assignedList[2], 300);
}