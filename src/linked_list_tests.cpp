#include <gtest/gtest.h>
#include <linked_list.h>
#include <string>

TEST(LinkedListTests, AppendPrependInsert) {
    LinkedList<int> list;
    list.append(2);
    list.prepend(1);
    list.insert(2, 3);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 3);
}

TEST(LinkedListTests, FindAndFindIndex) {
    LinkedList<std::string> list = { "apple", "banana", "cherry" };

    auto it = list.find("banana");
    EXPECT_EQ(*it, "banana");

    int idx = list.find_index("cherry");
    EXPECT_EQ(idx, 2);
}

TEST(LinkedListTests, Remove) {
    LinkedList<int> list = { 10, 20, 30, 40 };
    auto it = list.find(30);
    list.remove(it);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.find_index(30), -1);
}

TEST(LinkedListTests, RemoveAll) {
    LinkedList<int> list = { 5, 10, 5, 20, 5 };
    list.remove_all(5);

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], 10);
    EXPECT_EQ(list[1], 20);
}

TEST(LinkedListTests, ClearDestructor) {
    LinkedList<int> list = { 1, 2, 3 };
    list.clear();

    EXPECT_EQ(list.size(), 0);
}

TEST(LinkedListTests, CopyConstructorAssignment) {
    LinkedList<int> list1 = { 1, 2, 3 };
    LinkedList<int> list2(list1);

    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list2[1], 2);

    LinkedList<int> list3;
    list3 = list2;
    EXPECT_EQ(list3[2], 3);
}

TEST(LinkedListTests, MoveConstructorAssignment) {
    LinkedList<int> list1 = { 7, 8, 9 };
    LinkedList<int> list2(std::move(list1));

    EXPECT_EQ(list2.size(), 3);

    LinkedList<int> list3;
    list3 = std::move(list2);
    EXPECT_EQ(list3[1], 8);
}

TEST(LinkedListTests, IteratorTraversal) {
    LinkedList<int> list = { 1, 2, 3 };
    int sum = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 6);
}

TEST(LinkedListTests, ToStringOperatorOutput) {
    LinkedList<int> list = { 1, 2, 3 };
    EXPECT_EQ(list.to_string(), "[1, 2, 3]");
}