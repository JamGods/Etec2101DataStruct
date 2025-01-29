#pragma once
#include <person.h>
#include <string>

namespace example {
	class PersonDatabase {
	private:
		Person* people; ///< "Dyanamic" array of person objects
		int num_people; ///< Shows number of people in the database
		int capacity;   ///< this shows the maximum number of people you can fit in the array
		std::string tempfilename; ///< this is the file used for saving/loading database info
		/// <summary>
		/// This lets us wait for it.. resize our array!!
		/// </summary>
		void resize_array();
	public:
		/// <summary>
		/// This is the constructor for the PersonDatabase
		/// </summary>
		/// <param name="tempfilename">This is the file we're kind of storing the database in</param>
		PersonDatabase(const std::string& tempfilename); // a constructor oh boy
		~PersonDatabase(); // a deconstructor even crazier wowza

		//here come all the fun functions we need :D
		/// <summary>
		/// Add a person, its adds a person. Very succint naming scheme
		///  I know compliments to the chef or programmer I suppose
		/// </summary>
		/// <param name="person">This is the person being added to the database</param>
		void add_person(const Person& person);       
		/// <summary>
		/// Remove a person by ID, while you could remove someone by name that would cause some issues would it not
		///in fact imagine calling them by their age that would be funny
		/// </summary>
		/// <param name="id">The id of the person we want to remove</param>
		bool remove_person(int id);
		/// <summary>
		/// Get the number of people, shrimple little function not hard at all
		/// </summary>
		int get_num_people() const;
		/// <summary>
		/// Get a string representation who would have guessed it not me
		/// </summary>
		std::string to_string() const;
	};
}