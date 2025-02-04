#include <iostream>
#include <person.h>
#include <person_database.h>
#include <limits>
#include <string>
#include <stdexcept>one 
// All code commented out was just used to confrim that all the functions were working as intended
//However I will leave it here so you can take a look at it if you wish
using namespace example;
/*
void test_person_class() {
    std::cout << "Testing Person class...\n";

    // Test default constructor
    Person p1;
    if (p1.get_id() != -1 || p1.get_first_name() != "?" || p1.get_last_name() != "?" ||
        p1.get_hourly_rate() != 0.0f || p1.get_hours_worked() != 0) {
        std::cerr << "Default constructor test failed.\n";
        return;
    }

    // Test parameterized constructor
    Person p2(101, "John", "Doe");
    if (p2.get_id() != 101 || p2.get_first_name() != "John" || p2.get_last_name() != "Doe") {
        std::cerr << "Parameterized constructor test failed.\n";
        return;
    }

    // Test setters and getters
    p2.set_hourly_rate(25.5f);
    p2.set_hours_worked(40);
    if (p2.get_hourly_rate() != 25.5f || p2.get_hours_worked() != 40) {
        std::cerr << "Setters/Getters test failed.\n";
        return;
    }

    // Test calculate_pay
    if (p2.calculate_pay() != 25.5f * 40) {
        std::cerr << "calculate_pay() test failed.\n";
        return;
    }

    std::cout << "Person class tests passed.\n";
}
*/
/*
void test_person_database() {
    std::cout << "Testing PersonDatabase class...\n";
    // Create a database
    PersonDatabase db("test_database.txt");
    // Add persons with set hourly rate and hours worked
    Person p1(101, "Alice", "Johnson");
    Person p2(102, "Bob", "Smith");
    // Assign hourly rates and hours worked
    p1.set_hourly_rate(25.5f);
    p1.set_hours_worked(40);
    p2.set_hourly_rate(25.5f);
    p2.set_hours_worked(40);
    // Debug: Print the details before adding them
    std::cout << "Adding Person 1: " << p1.get_first_name() << " " << p1.get_last_name()
        << ", Rate: $" << p1.get_hourly_rate() << ", Hours: " << p1.get_hours_worked() << "\n";
    std::cout << "Adding Person 2: " << p2.get_first_name() << " " << p2.get_last_name()
        << ", Rate: $" << p2.get_hourly_rate() << ", Hours: " << p2.get_hours_worked() << "\n";
    db.add_person(p1);
    db.add_person(p2);
    // Check number of people
    if (db.get_num_people() != 2) {
        std::cerr << "Adding person test failed.\n";
        return;
    }
    // Check database string representation
    std::cout << "Database Contents:\n" << db.to_string() << "\n";
    std::cout << "PersonDatabase class tests passed.\n";
}
*/
int main() {
    /*test_person_class();
    test_person_database();
    std::cout << "All tests passed successfully.\n";*/
    PersonDatabase database("../media/database.txt");
    int choice;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Person\n";
        std::cout << "2. Remove Person\n";
        std::cout << "3. Print Database\n";
        std::cout << "4. Edit Person\n";
        std::cout << "5. Quit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        if (choice == 1) {
            int id;
            std::string first_name, last_name;
            float hourly_rate;
            unsigned int hours_worked;
            // ID input with validation
            std::cout << "Enter ID (max 3 digits): ";
            std::cin >> id;
            while (std::cin.fail() || id < 0 || id > 999) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid ID. Please enter a valid 3-digit ID (0-999): ";
                std::cin >> id;
            }
            std::cout << "Enter First Name: ";
            std::cin >> first_name;
            std::cout << "Enter Last Name: ";
            std::cin >> last_name;
            std::cout << "Enter Hourly Rate: ";
            std::cin >> hourly_rate;
            std::cout << "Enter Hours Worked: ";
            std::cin >> hours_worked;
            try {
                Person person(id, first_name, last_name);
                person.set_hourly_rate(hourly_rate);
                person.set_hours_worked(hours_worked);
                database.add_person(person);
                std::cout << "Person added successfully.\n";
            }
            catch (const std::runtime_error& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        }
        else if (choice == 2) {
            int id;
            std::cout << "Enter ID to remove: ";
            std::cin >> id;
            // ID input with validation for removal
            while (std::cin.fail() || id < 0 || id > 999) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid ID. Please enter a valid 3-digit ID (0-999): ";
                std::cin >> id;
            }
            if (database.remove_person(id)) {
                std::cout << "Person removed successfully.\n";
            }
            else {
                std::cout << "Person not found.\n";
            }
        }
        else if (choice == 3) {
            std::cout << database.to_string() << "\n";
        }
        else if (choice == 4) {
            int id;
            std::cout << "Enter ID to look up: ";
            std::cin >> id;
            // ID input with validation for lookup
            while (std::cin.fail() || id < 0 || id > 999) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid ID. Please enter a valid 3-digit ID (0-999): ";
                std::cin >> id;
            }
            Person* person = database.get_person_by_id(id);
            if (person) {
                std::cout << "Found: " << person->get_first_name() << " " << person->get_last_name() << "\n";
                float new_rate;
                unsigned int new_hours;
                std::cout << "Enter new hourly rate: ";
                std::cin >> new_rate;
                std::cout << "Enter new hours worked: ";
                std::cin >> new_hours;
                person->set_hourly_rate(new_rate);
                person->set_hours_worked(new_hours);
                std::cout << "Person updated successfully.\n";
            }
            else {
                std::cout << "Person not found.\n";
            }
        }
        else if (choice == 5) {
            std::cout << "Exiting program.\n";
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}