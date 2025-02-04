#ifndef _PERSON_H_    // "compiler guard" -- ensures this header file is only included once
#define _PERSON_H_

#include <string>

namespace example
{
    class Person
    {
    private:
        int id;  ///< Unique identifier for the person
        std::string first_name; ///< First name of the person
        std::string last_name;  ///< Last name of the person
        float hourly_rate;  ///< Hourly pay rate
        unsigned int hours_worked; ///< Number of hours worked

    public:
        // This is the CONSTRUCTOR -- a method that has no return type and MUST 
        // have the same name as the class. This is a DEFAULT CONSTRUCTOR (no parameters)
        Person();
        // This is ANOTHER CONSTRUCTOR (this is an OVERLOAD...alternate version) of the constructor
        /// <summary>
        /// This is a non-default constructor -- mostly initializes all parameters
        /// based on arguments from the caller
        /// </summary>
        /// <param name="start_id">This is the id# for the new Person</param>
        /// <param name="start_fname">This is the first name for a new Person</param>
        /// <param name="start_lname">This is the last name for a new Person</param>
        Person(int start_id, std::string start_fname, std::string start_lname);
        // This is the DESTRUCTOR. This is called when an instance is about to go "away",
        // This method gets called. It is unusual to call this manually. More often, it's
        // called when an instance goes out of scope (scope is where that variable is visible, or
        // is defined). Do any kind of cleanup you wish. Biggie: if you dynamically allocated
        // any memory, this is a good place to clean it up.
        /// <summary>Deconstructor</summary>
        ~Person();
        // This is a METHOD -- a function that all instances of the class can
        // use. This is a DECLARATION.
        /// <summary>
        /// This calculates the pay.
        /// </summary>
        float calculate_pay();
        // These are examples of SETTERS
        /// <summary>
        /// Sets the hourly rate.
        /// </summary>
        /// <param name="new_rate">The new hourly rate</param>
        void set_hourly_rate(float new_rate);
        /// <summary>
        /// Sets the hours worked.
        /// </summary>
        /// <param name="new_hours">The number of hours worked</param>
        void set_hours_worked(unsigned int new_hours);
        // These are examples of GETTERS
        /// <summary>
        /// Gets the person's ID.
        /// </summary>
        int get_id() const;
        /// <summary>
        /// Gets the first name of the person.
        /// </summary>
        std::string get_first_name() const;
        /// <summary>
        /// Gets the last name of the person.
        /// </summary>
        std::string get_last_name() const;
        /// <summary>
        /// Gets the hours worked by the person.
        /// </summary>
        unsigned int get_hours_worked() const;
        /// <summary>
        /// Gets the hourly rate of the person.
        /// </summary>
        float get_hourly_rate() const;
    };
}

#endif