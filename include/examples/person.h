#ifndef _PERSON_H_ //keeps things from being multi-defined
#define _PERSON_H_

#include <string>
class Person
{
private:
	int id;
	std::string first_name;
	std::string last_name;
	float hourly_rate;
	unsigned int hours_worked;
public:
	//This is just a constructor has no return type and MUST have the class name
	//This would be considered a default constructor
	Person();

	//This is an alternate constructor
	Person(int start_id, std::string start_fname, std::string start_lname);
	//Method example -- a func that all instances of class can use
	float calculate_pay();
	//These are consider SETTERS
	void set_hourly_rate(float new_rate);
	void set_hours_worked(unsigned int new_hours);

	//These are the opposite GETTERS
	int get_id();
	std::string get_first_name();
	std::string get_last_name();
	unsigned int get_hours_worked();
	float get_hourly_rate();
};

#endif