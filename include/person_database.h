#pragma once
#include <person.h>
#include <string>

namespace example {
	class PersonDatabase {
	private:
		Person* people; // "Dyanamic" array of person objects--Do not forget this thats why you added a comment
		int num_people; // another important one this shows the current number of peeps in the base
		int capacity;   // this shows the maximum number of people you can fit in the array
		std::string tempfilename; //this is the file used for saving/loading database info or it will be lol

		void resize_array(); //this is the method I've decided will help resize the array creative name I know
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="tempfilename">This is the file we're kind of storing the database in</param>
		PersonDatabase(const std::string& tempfilename); // a constructor oh boy
		~PersonDatabase(); // a deconstructor even crazier wowza

		//here come all the fun functions we need :D
		void add_person(const Person& person);       // Add a person very succint naming scheme I know compliments to the chef or coder ig(thats actually me haha)
		bool remove_person(int id);                  // Remove a person by ID, while you could remove someone by name that would cause some issues would it not
													 //in fact imagine calling them by their age that would be funny
		int get_num_people() const;                  // Get the number of people, shrimple little function not hard at all
		std::string to_string() const;               // Get a string representation, this one will be much harder to figure out, can't wait to work on the cpp file
	};
}