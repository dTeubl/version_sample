/** 
 * This a sample program to demonstrate an easy way of version number
 * indication using git tools. The main goal is to create a example 
 * application and toolchain, in which, the application itself has its
 * current version number build inside as a constant variable. This version 
 * number should be the same as the result of the "git describe" command.
 *
 * These program depend on the usage of a well prepared pre-commit-hook,
 * and a wrapper script around the normal "git tag -a" command
 *
 */

#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include "fwid.h"

int main(int argc, char *argv[] ) {

    try{ 

    std::cout << argc << std::endl;

    if( argc < 3 )
        throw("not enough input arguments");

    // Checking the input arguments
    for(int i=0; i<argc; ++i)
        std::cout << i << ": " << argv[i] << "\t";

    
//=========================== FWID modification ===============================
// Setting up for the right part to be able to modify the describing structure 
// in the fwid.cpp file.

    std::cout << "\n================================\n" << std::endl;


    std::string reg_tag{};
    reg_tag+="([ ]*[a-zA-Z]*)(.)(tag_ = \")(v[0-9]*)(.)([0-9]*)(\")(.)*"; // <---- This is the one!
    std::string reg_branch{};
    reg_branch+= "([ ]*[a-zA-Z]*)(.)(branch_ = \")([a-zA-Z0-9]*)(\")(.)*"; // <---- This is the one!

    std::string reg_buildNum{};
    reg_buildNum+= "([ ]*[a-zA-Z]*)(.)(buildNum_ = )([0-9]*)(.)*"; // <---- This is the one!

//     std::regex base_reg{reg_tag};
//     std::regex base_reg{reg_branch};
    std::regex reg{reg_buildNum};
    std::smatch res;
    std::string line;

    std::fstream file2 {"fwid.cpp",std::ios::in | std::ios::out };

    while( std::getline(file2,line)) {

        std::cout << line << std::endl;

        if( std::regex_match(line,res,reg) ) {

            std::cout << "found it!" << std::endl;
        }
    }


    }
    catch(const char* e)  {
        std::cout << e << std::endl;
    }

    return 0;
}
