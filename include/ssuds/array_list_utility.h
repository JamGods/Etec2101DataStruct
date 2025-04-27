#ifndef ARRAY_LIST_UTILITY_H
#define ARRAY_LIST_UTILITY_H

#include <vector>
#include <random>
#include <chrono>
#include <array_list.h>

enum class SortOrder { ASCENDING, DESCENDING };

template <typename T>
int partition(std::vector<T>& arr, int low, int high, SortOrder order) {
    T pivot = arr[high];
    int i = low - 1;
    int swaps = 0;

    for (int j = low; j < high; j++) {
        if ((order == SortOrder::ASCENDING && arr[j] < pivot) ||
            (order == SortOrder::DESCENDING && arr[j] > pivot)) {
            i++;
            std::swap(arr[i], arr[j]);
            swaps++;
        }
    }
    std::swap(arr[i + 1], arr[high]);
    swaps++;
    return i + 1;
}

template <typename T>
int quicksortHelper(std::vector<T>& arr, int low, int high, SortOrder order) {
    int swaps = 0;
    if (low < high) {
        int pivotIndex = partition(arr, low, high, order);
        swaps += quicksortHelper(arr, low, pivotIndex - 1, order);
        swaps += quicksortHelper(arr, pivotIndex + 1, high, order);
    }
    return swaps;
}

template <typename T>
int quicksort(std::vector<T>& arr, SortOrder order) {
    return quicksortHelper(arr, 0, arr.size() - 1, order);
}

template <typename T>
int bubble_sort(std::vector<T>& arr, SortOrder order) {
    int swaps = 0;
    bool swapped;
    for (size_t i = 0; i < arr.size() - 1; i++) {
        swapped = false;
        for (size_t j = 0; j < arr.size() - i - 1; j++) {
            if ((order == SortOrder::ASCENDING && arr[j] > arr[j + 1]) ||
                (order == SortOrder::DESCENDING && arr[j] < arr[j + 1])) {
                std::swap(arr[j], arr[j + 1]);
                swaps++;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    return swaps;
}

template <typename T>
int binary_search(const std::vector<T>& arr, SortOrder order, T value) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == value)
            return mid;
        if ((order == SortOrder::ASCENDING && arr[mid] < value) ||
            (order == SortOrder::DESCENDING && arr[mid] > value))
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

template <typename T>
void shuffle(std::vector<T>& arr) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(arr.begin(), arr.end(), g);
}

#endif