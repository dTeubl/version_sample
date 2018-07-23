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
    int buildNum=0;

    try{ 

    std::cout << argc << std::endl;

    if( argc <= 3 )
        throw("Not enough input arguments");

    // Checking the input arguments
    for(int i=0; i<argc; ++i)
        std::cout << i << ": " << argv[i] << "\t";

    // Read out the build number

    std::string gitVer{argv[3]};
    std::cout << gitVer << std::endl;

    std::string reg_value{};
    reg_value+="(.)*-([0-9]+)-(.)*"; // <---- This is the one!

    std::regex base_reg{reg_value};
    std::smatch match;

    std::cout << "result:\t" << std::regex_match(gitVer,match,base_reg) << std::endl;

    std::cout << match.size() << std::endl;
    for( size_t i=1; i<match.size(); i++)
        std::cout << "match " << i << ": "<< match.str(i) << ";\n";
    
    std::cout << std::endl;

    buildNum = static_cast<unsigned int>(std::stoi(match.str(2)));

    
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
