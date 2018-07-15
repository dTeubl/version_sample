/** 
 * From the given input string determine the version of a program.
 *
 */

#include <iostream>
#include <regex>
#include <string>

int main(int argc, char *argv[] ) {

    try{
    std::cout << argc << std::endl;

    for(int i=0; i<argc; ++i)
        std::cout << argv[i] << "\t";

    std::cout << std::endl;;

//     std::string gitVer=argv[1];
    std::string gitVer{argv[1]};

    std::cout << gitVer << std::endl;

    std::cout << std::endl;;
    }
    catch(const char* e)  {
        std::cout << e << std::endl;
    }

    return 0;
}
