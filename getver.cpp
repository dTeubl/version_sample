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

/**
 * This structure holds the key informations about this sofrware. All of
 * these informations are written in here by the program itself, at a 
 * specific time before each commit.
 */
typedef struct t_fwid {
    std::string tag_ = "v1.0";
    std::string branch_ = "master";
    unsigned int buildNum_ = 0;
} FWID;


FWID myFwId;


int main(int argc, char *argv[] ) {

    myFwId.tag_ = "v1.0";
    myFwId.branch_ = "master";
    myFwId.buildNum_ = 0;


    unsigned int MAGIC = 4;

    try{ 

    std::cout << argc << std::endl;

    if( argc < 3 )
        throw("not enough input arguments");

    for(int i=0; i<argc; ++i)
        std::cout << i << ": " << argv[i] << "\t";

    std::cout << std::endl;;

//     std::string gitVer=argv[1];
    std::string gitVer{argv[1]};
    std::cout << gitVer << std::endl;

    std::string reg_value{};
    reg_value+="(v[0-9]*.[0-9]*)-([0-9]+)-(.)*"; // <---- This is the one!

    std::regex base_reg{reg_value};
    std::smatch match;

    std::cout << "result:\t" << std::regex_match(gitVer,match,base_reg) << std::endl;

    std::cout << match.size() << std::endl;
    for( size_t i=1; i<match.size(); i++)
        std::cout << "match " << i << ": "<< match.str(i) << ";\n";
    
    std::cout << std::endl;

    MAGIC = static_cast<unsigned int>(std::stoi(match.str(2)));




    // Now the MAGIC part, We should rewrite the value of the MAGIC variable!!
    
   
    std::fstream file{"getver.cpp",std::ios::in | std::ios::out };
    std::string line;

    // This line preservs the other data in the line
    std::string reg_magic{"(([ ]*[a-zA-Z]*)*)(MAGIC)( = )([0-9]+)(.)*"};
//     std::string reg_magic{"(.)*(MAGIC)( = )([0-9]+)(.)*"}; // <<<----this works
    std::regex base{reg_magic};
    std::smatch res{};



    // Now read until we find the MAGIC, than replace!
    
    std::cout << "reading file: " << "getver.cpp" << std::endl;

    int mypos = file.tellp( );
    int lastpos = 0;
    int lnum = 0;
    std::cout << "my position: " << mypos << std::endl;

    while( std::getline(file,line)) {
            
        lastpos = mypos;
        mypos = file.tellp();
        std::cout << "line number: " << lnum++ <<"\tmy position: " << mypos << std::endl;

        if( std::regex_match(line,res,base) ) {

            std::cout << res.size() << std::endl;
            for( size_t i=1; i<res.size(); i++)
                std::cout << "res " << i << ": "<< res.str(i) << ";\n";
            
            std::cout << std::endl;

            std::cout << line << std::endl;
            std::string nl{};
            nl+=res.str(1);
            nl+=res.str(3);
            nl+=res.str(4);
            nl+=match.str(2);
    //         nl+=std::string{MAGIC+1};
            nl+=res.str(6);

            std::cout << "new line is: " << nl << std::endl;

            if( res.str(3) == "MAGIC" ) {
                std::cout << "We have it now!" << std::endl;
                file.seekp(lastpos);
                file << nl << "\n";  //<<--- this also works
                break;
            }

        } // We foun something!
    } // while( )

    file.close();

    }
    catch(const char* e)  {
        std::cout << e << std::endl;
    }

    return 0;
}
