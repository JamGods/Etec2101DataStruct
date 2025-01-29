// person_database.cpp -- houses the BODIES (DEFINITIONS) of all methods for persondatabase class
#include "person_database.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
//this line allows me to not type example:: every single time
using namespace example;

// the constructor just learned about this guy
PersonDatabase::PersonDatabase(const std::string& tempfilename)
    : people(nullptr), num_people(0), capacity(0), tempfilename(tempfilename) {
    std::ifstream file(tempfilename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            int id;
            std::string first_name, last_name;
            iss >> id >> first_name >> last_name;
            Person person(id, first_name, last_name);
            add_person(person);
        }
        file.close();
    }
}
//now onto the deconstructor :D
PersonDatabase::~PersonDatabase() {
    std::ofstream file(tempfilename);
    if (file.is_open()) {
        for (int i = 0; i < num_people; ++i) {
            file << people[i].get_id() << " " << people[i].get_first_name() << " " << people[i].get_last_name() << "\n";
        }
        file.close();
    }
    delete[] people;
}
// This is how you add a person woohoo onto something more interesting
void PersonDatabase::add_person(const Person& person) {
    for (int i = 0; i < num_people; ++i) {
        if (people[i].get_id() == person.get_id()) {
            throw std::runtime_error("This is a duplicate ID");
        }
    }
    if (num_people == capacity) {
        resize_array();
    }
    people[num_people++] = person;
}
//after this we can remove that guy
bool PersonDatabase::remove_person(int id) {
    for (int i = 0; i < num_people; ++i) {
        if (people[i].get_id() == id) {
            for (int j = i; j < num_people - 1; ++j) {
                people[j] = people[j + 1];
            }
            --num_people;
            resize_array();
            return true;
        }
    }
    return false;
}
//then we can get the number of people down here :o
int PersonDatabase::get_num_people() const {
    return num_people;
}
//the to_string function it formats it, very cool
std::string PersonDatabase::to_string() const{
    std::stringstream ss;
    // Table header
    ss << "Person        ID    Hours   Rate     Monthly Salary\n";
    ss << "=====         ==    =====   ====     ==============\n";
    float total_salary = 0.0f;
    // Loop through each person in the database
    for (int i = 0; i < num_people; ++i) {
        const Person& person = people[i];
        float monthly_salary = person.get_hourly_rate() * person.get_hours_worked();
        // Add person's details in a formatted way
        ss << std::left << std::setw(13) << (person.get_first_name() + " " + person.get_last_name())//wraps down
           << std::setw(6) << person.get_id() << std::setw(8) << person.get_hours_worked()//wraps down
           << "$" << std::fixed << std::setprecision(2) << std::setw(8) << person.get_hourly_rate()//wraps down
           << "$" << std::fixed << std::setprecision(2) << monthly_salary << "\n";
        // Add to the total salary
        total_salary += monthly_salary;
    }
    // Footer with total salary
    ss << "====================================================\n";
    ss << "Total: $" << std::fixed << std::setprecision(2) << total_salary;
    return ss.str();
}
//lets resize our array 
void PersonDatabase::resize_array() {
    int new_capacity = (capacity == 0) ? 1 : capacity * 2;
    Person* new_array = new Person[new_capacity];
    for (int i = 0; i < num_people; ++i) {
        new_array[i] = people[i];
    }
    delete[] people;
    people = new_array;
    capacity = new_capacity;
}