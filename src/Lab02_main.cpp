#include <iostream>
#include <array_list.h>

int main() {
    ssuds::ArrayList<float> float_list;
    //The Jason approved testing visuals :D
    std::cout << "=== Test 1: Append ===\n";
    float_list.append(2.1f);
    float_list.append(3.6f);
    std::cout << "Size: " << float_list.size() << ", List: " << float_list << "\n\n";

    std::cout << "=== Test 2: Insert ===\n";
    float_list.insert(1.8f, 0);  // Insert at beginning
    float_list.insert(4.2f, 3);  // Insert at end (like append)
    float_list.insert(2.0f, 1);  // Insert in the middle
    std::cout << "List after inserts: " << float_list << "\n\n";

    std::cout << "=== Test 3: Prepend ===\n";
    float_list.prepend(0.5f);
    std::cout << "List after prepend: " << float_list << "\n\n";

    std::cout << "=== Test 4: Access (at) ===\n";
    std::cout << "Element at index 2: " << float_list.at(2) << "\n\n";

    std::cout << "=== Test 5: Remove ===\n";
    float removed = float_list.remove(1);
    std::cout << "Removed: " << removed << ", List after removal: " << float_list << "\n\n";

    std::cout << "=== Test 6: Remove All ===\n";
    float_list.append(3.6f); // Add another 3.6 to test remove_all
    int removed_count = float_list.remove_all(3.6f);
    std::cout << "Removed " << removed_count << " occurrences, List: " << float_list << "\n\n";

    std::cout << "=== Test 7: Find ===\n";
    float_list.append(4.2f);
    float_list.append(5.5f);
    int found_index = float_list.find(4.2f);
    std::cout << "Index of 4.2: " << found_index << "\n\n";

    std::cout << "=== Test 8: Size & Capacity ===\n";
    std::cout << "Size: " << float_list.size() << ", Capacity: " << float_list.capacity() << "\n\n";

    std::cout << "=== Test 9: Reserve ===\n";
    float_list.reserve(20);
    std::cout << "Capacity after reserve(20): " << float_list.capacity() << "\n\n";

    return 0;
}