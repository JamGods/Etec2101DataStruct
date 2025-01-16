#include <iostream>
#include <person.h>
#include <string> // <string.h> is the C string library not this
using namespace std; //Makes the std optional, however might make reading code a little difficult if you weren't the one who wrote it
int main()
{
    char s;
    s = 'a';
    char c_string[64] = "bob";
    const char* c_string2 = "sally";
    printf("c_string = %s\n", c_string);
    strcpy_s(c_string, 64, "robert");
    printf("c_string = %s\n", c_string);
    printf("test=%d\n", strcmp(c_string, "moo"));
    if (strcmp(c_string, "moo") > 0)
        printf("%s comes after \"moo\"\n", c_string);

    //same as above now with C++ instead
    std::string cpp_string = "bob"; // this is simply an instance of the sting class called cpp_string, std:: is the name space so std::string is the standard string namespace
    std::cout << cpp_string << "\n"; // C++ style console output -- a taste of a c++ STREAM (this is an output stream which is why << goes to the left, >> would be input)
    int x = 42;
    std::cout << "a string " << x << "\n";
    cpp_string[0] = 'r'; // The [] operatore is OVERLOADED for strings
    cpp_string[1] = 'o';
    cpp_string[2] = 0;
    std::cout << cpp_string << "\n";
    cpp_string = "robert"; // the class handles everything for you
    if (cpp_string > "moo") // this calls strcmp for you
        std::cout << cpp_string << " comes after \"moo\"\n";
    c_string2 = cpp_string.c_str(); //getting thie underlying c string.. so we can use all our c functions.

    Person p;
    p.id = 42;
    p.first_name = "Bob";
    Person q;
    q.id = 43;
    q.first_name = "Sally";
}