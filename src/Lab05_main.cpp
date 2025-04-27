#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <array_list_utility.h>

void benchmark() {
    std::ofstream file("performance_results.csv");
    file << "ArraySize,QuicksortTime,BubbleSortTime,BinarySearchTime,LinearSearchTime\n";

    for (size_t size = 1000; size <= 1000000; size += 5000) {
        std::vector<float> arr(size);
        for (size_t i = 0; i < size; i++) arr[i] = i + 0.5f;

        std::vector<float> shuffledArr = arr;
        shuffle(shuffledArr);
        std::vector<float> searchTargets(shuffledArr.begin(), shuffledArr.begin() + 1000);
        auto start = std::chrono::high_resolution_clock::now();
        quicksort(shuffledArr, SortOrder::ASCENDING);
        auto quicksortTime = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - start
        ).count();

        long long bubbleSortTime = 0;
        if (size <= 300000) {
            shuffledArr = arr;
            shuffle(shuffledArr);

            start = std::chrono::high_resolution_clock::now();
            bubble_sort(shuffledArr, SortOrder::ASCENDING);
            bubbleSortTime = std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::high_resolution_clock::now() - start
            ).count();
        }

        start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < 1000; i++)
            binary_search(arr, SortOrder::ASCENDING, searchTargets[i]);
        auto binarySearchTime = std::chrono::duration_cast<std::chrono::nanoseconds >(
            std::chrono::high_resolution_clock::now() - start
        ).count();

        start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < 1000; i++) {
            auto it = std::find(arr.begin(), arr.end(), searchTargets[i]);
        }
        auto linearSearchTime = std::chrono::duration_cast<std::chrono::nanoseconds > (
            std::chrono::high_resolution_clock::now() - start
        ).count();

        file << size << "," << quicksortTime <<"," << bubbleSortTime << ","
            << binarySearchTime << "," << linearSearchTime << "\n";

        std::cout << "Completed size " << size << std::endl;
    }

    file.close();
}

int main() {
    std::cout << "Starting benchmark..." << std::endl;
    benchmark();
    std::cout << "Benchmark complete. Results saved in performance_results.csv" << std::endl;
    return 0;
}
