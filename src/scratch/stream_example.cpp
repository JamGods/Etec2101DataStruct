#include <iostream>
#include <string>
#include <fstream>     // access to FILE input/output

#define DO_FILE_OUTPUT 0

int main(int argc, char** argv)
{
#if DO_FILE_OUTPUT
	int x = 42;
	std::string s;
	std::cout << "x = " << x << "\n";

	std::cout << "Enter a value for x: ";
	std::cin >> x;							// Note how chevrons go to the right
	if (std::cin.fail())
	{
		std::cout << "There was an error reading the value\n";
		x = -1;
		// cin attempted to read an integer, but failed.  cin consumed
		// the text we entered, but the newline is still in the buffer.  Also
		// cin is in an error state right now.  To fix both:
		std::cin.clear();		// Clears the errors state
		std::cin.ignore(1000, '\n');   // Gets rid of any remaining garbage
									   // and consumes the \n
	}
	std::cout << "x now equals " << x << "\n";

	std::cout << "Enter a string (without whitespace): ";
	// This reads a string or until whitespace is reached.  Any future cin's
	// will use the remaining strings in the buffer.  Note how after getting our
	// string, I use ignore to consume anything ELSE in the buffer (including
	// the newline)
	std::cin >> s;
	std::cin.ignore(1000, '\n');
	std::cout << "s now equals '" << s << "'\n";

	std::cout << "Enter a string with whitespace: ";
	// getline reads from cin into s until \n is reached
	std::getline(std::cin, s);
	std::cout << "s now equals '" << s << "'\n";



	// FILE OUTPUT
	std::ofstream fp("..\\..\\media\\test.txt");     // o=output (text-file by default)
	fp << "This is a line\n";		  // Just like cout!!
	fp << "x = " << x << "\n";
	fp << "And we're done!\n";
	fp.close();
#else

	// FILE INPUT
	std::ifstream fp("..\\..\\media\\test.txt");
	if (!fp.is_open())
	{
		std::cout << "Error opening ..\\..\\media\\test.txt \n";
		return 1;
	}

	std::string temp_line;
	std::getline(fp, temp_line);
	std::cout << "Line0=" << temp_line << "\n";

	// Line2 is of the form "x = 99" -- how to get the number?
	fp.ignore(4, '\n');
	int real_x;
	fp >> real_x;
	fp.ignore(1000, '\n');
	std::cout << "got x's value of " << real_x << "\n";

	std::getline(fp, temp_line);
	std::cout << "Line2=" << temp_line << "\n";

	fp.close();
#endif

	return 0;
}