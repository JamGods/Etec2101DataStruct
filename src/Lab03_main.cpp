#include <iostream>
#include <array_list.h>

int main() {
    ssuds::ArrayList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);

    std::cout << "ArrayList contents: " << list << std::endl;

    std::cout << "Using forward iterator: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Using reverse iterator: ";
    if (list.size() > 0) {
        for (auto it = list.rbegin(); it != list.rend(); ++it) {
            std::cout << *it << " ";
        }
    }
    std::cout << std::endl;

    std::cout << "Element at index 2: " << list[2] << std::endl;

    ssuds::ArrayList<int> copyList = list;
    std::cout << "Copied List: " << copyList << std::endl;

    ssuds::ArrayList<int> movedList = std::move(copyList);
    std::cout << "Moved List (should be same as original): " << movedList << std::endl;

    ssuds::ArrayList<int> initList = { 10, 20, 30, 40 };
    std::cout << "Initializer List: " << initList << std::endl;

    if (list.find(3) != list.end()) {
        std::cout << "Found 3 in the list!" << std::endl;
    }

    list.remove(3);
    std::cout << "List after removing 3: " << list << std::endl;
    return 0;
}