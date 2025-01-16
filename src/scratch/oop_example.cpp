#include <person.h>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    // Making two instances/objects of the Person class
    Person p(42, "Bob", "Jones"); // using "real" constructor
    Person q; // using default constructor

    p.set_hourly_rate(13.5f);
    p.set_hours_worked(17);

    std::cout << "The Pay for p is " << p.calculate_pay() << "\n";
    std::cout << "The Pay for q is " << q.calculate_pay() << "\n";

	return 0;
}