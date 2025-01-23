#include <iostream>
#include <string>     // <string.h> is the C string library (not this)
using namespace std;  // Makes the std:: on stuff optional

int main()
{
    // C-strings
    char s;        // an integer, usually 1 byte.  
    s = 'a';        // 97
    char c_string[64] = "bob";      // 98, 111, 98, 0, ?, ?, ...., ?
    const char* c_string2 = "sally";// in the global variable section of our process
    printf("c_string = %s\n", c_string);
    //c_string = "robert";
    c_string[0] = 'r';
    c_string[1] = 'o';
    c_string[2] = 0;
    strcpy_s(c_string, 64, "robert");
    printf("c_string = %s\n", c_string);
    printf("test=%d\n", strcmp(c_string, "moo"));
    if (strcmp(c_string, "moo") > 0)
        printf("%s comes after \"moo\"\n", c_string);
    

    // Same, but with C++
    std::string cpp_string = "bob";     // making an INSTANCE of the string class called cpp_string
                                        // std is the NAMESPACE that the string class exists in
    std::cout << cpp_string << "\n";    // C++ style console output -- a taste of c++ STREAMS (this
                                        //   is an output stream which is why  << goes to the left.
    int x = 42;
    std::cout << "a string" << x << "\n";
    cpp_string[0] = 'r';                // The [] operator is OVERLOADED for strings
    cpp_string[1] = 'o';
    cpp_string[2] = 0;
    std::cout << cpp_string << "\n";
    cpp_string = "robert";              // The class handles the memory copy and making enough space
                                        //   to hold this new string (nice!)
    if (cpp_string > "moo")             // Internally probably calling strcmp
        std::cout << cpp_string << " comes after \"moo\"\n";
    c_string2 = cpp_string.c_str();     // Getting the underlying C string...so we can use all our
                                        //   c functions.
}