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

    if( argc < 3 )
        throw("not enough input arguments");

    for(int i=0; i<argc; ++i)
        std::cout << i << ": " << argv[i] << "\t";

    std::cout << std::endl;;

//     std::string gitVer=argv[1];
    std::string gitVer{argv[1]};
    std::cout << gitVer << std::endl;

    std::string reg_value{};
//    reg_value+="(v(.)*(-)[0-9]*(.))"; // not working
//     reg_value+="((.)*(-)[0-9]*)";
//     reg_value+="((.)*)";
    reg_value+="(.)*-([0-9]+)-(.)*";

    std::regex base_reg{reg_value};
//     std::regex base_reg{std::string{argv[2]},std::regex_constants::extended};
    std::smatch match;

    std::cout << "result:\t" << std::regex_match(gitVer,match,base_reg) << std::endl;

    std::cout << match.size() << std::endl;
    for( size_t i=1; i<match.size(); i++)
        std::cout << "match " << i << ": "<< match.str(i) << ";\n";
    
    std::cout << std::endl;


    }
    catch(const char* e)  {
        std::cout << e << std::endl;
    }

    return 0;
}
