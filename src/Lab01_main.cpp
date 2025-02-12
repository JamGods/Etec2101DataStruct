#include <iostream>
#include <person.h>
#include <person_database.h>
#include <limits>
#include <string>
#include <stdexcept>
using namespace example;
int main() {
	PersonDatabase database("../../media/database.txt"); // Correct file path
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
			// ID input validation
			std::cout << "Enter ID (0-999): ";
			while (!(std::cin >> id) || id < 0 || id > 999) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid ID. Please enter a number between 0-999: ";
			}
			std::cout << "Enter First Name: ";
			std::cin >> first_name;
			std::cout << "Enter Last Name: ";
			std::cin >> last_name;
			// Hourly Rate validation
			std::cout << "Enter Hourly Rate (0.01 - 1000): ";
			while (!(std::cin >> hourly_rate) || hourly_rate < 0.01f || hourly_rate > 1000.0f) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid rate. Please enter a number between 0.01 and 1000: ";
			}
			// Hours Worked validation
			std::cout << "Enter Hours Worked (0 - 168): ";
			while (!(std::cin >> hours_worked) || hours_worked > 168) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid hours. Enter a number between 0 and 168: ";
			}
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
			while (!(std::cin >> id) || id < 0 || id > 999) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid ID. Please enter a number between 0-999: ";
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
			while (!(std::cin >> id) || id < 0 || id > 999) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid ID. Please enter a number between 0-999: ";
			}
			Person* person = database.get_person_by_id(id);
			if (person) {
				std::cout << "Found: " << person->get_first_name() << " " <<
					person->get_last_name() << "\n";
				float new_rate;
				unsigned int new_hours;
				std::cout << "Enter new hourly rate (0.01 - 1000): ";
				while (!(std::cin >> new_rate) || new_rate < 0.01f || new_rate > 1000.0f) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Invalid rate. Please enter a number between 0.01 and 1000: ";
				}
				std::cout << "Enter new hours worked (0 - 168): ";
				while (!(std::cin >> new_hours) || new_hours > 168) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Invalid hours. Enter a number between 0 and 168: ";
				}
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