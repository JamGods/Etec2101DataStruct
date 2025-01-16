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
	//Method example -- a func that all instances of class can use
	float calculate_pay();
};

#endif