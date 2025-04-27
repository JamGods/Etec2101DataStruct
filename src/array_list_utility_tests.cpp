/*#include <gtest/gtest.h>
#include <array_list_utility.h>

TEST(QuicksortTest, SortAscending) {
    std::vector<int> arr = { 3, 1, 4, 1, 5, 9, 2, 6 };
    quicksort(arr, SortOrder::ASCENDING);
    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

TEST(QuicksortTest, SortDescending) {
    std::vector<int> arr = { 3, 1, 4, 1, 5, 9, 2, 6 };
    quicksort(arr, SortOrder::DESCENDING);
    EXPECT_TRUE(std::is_sorted(arr.rbegin(), arr.rend()));
}

TEST(BinarySearchTest, FoundElement) {
    std::vector<int> arr = { 1, 2, 3, 4, 5 };
    EXPECT_EQ(binary_search(arr, SortOrder::ASCENDING, 3), 2);
}

TEST(BinarySearchTest, NotFoundElement) {
    std::vector<int> arr = { 1, 2, 3, 4, 5 };
    EXPECT_EQ(binary_search(arr, SortOrder::ASCENDING, 10), -1);
}

TEST(ShuffleTest, ChangesOrder) {
    std::vector<int> arr = { 1, 2, 3, 4, 5 };
    std::vector<int> copy = arr;
    shuffle(arr);
    EXPECT_NE(arr, copy);
}
*/