/** 
 * From the given input string determine the version of a program.
 *
 */

#include <iostream>
#include <fstream>
#include <regex>
#include <string>

int main(int argc, char *argv[] ) {

    unsigned int MAGIC = 3;

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
    reg_value+="(.)*-([0-9]+)-(.)*"; // <---- This is the one!

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
    std::string reg_magic{"(([ ]*[a-zA-Z]*)*)(MAGIC)( = )([0-9]+)(.)*"};
//     std::string reg_magic{"(.)*(MAGIC)( = )([0-9]+)(.)*"}; // <<<----this works
    std::regex base{reg_magic};
    std::smatch res{};
    // Now read until we find the MAGIC, than replace!
    
    std::cout << "reading file: " << "getver.cpp" << std::endl;
    std::string vers{};
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
