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


// The next three function do the main job, and rewrites the right line 
// in the file buffer. It is a dirty sollution, cus every function rewrites 
// every line, even if it is not needed. 

/**
 * Finds the line which contain the tag_ value and refresh the whole line
 * l: current line of the file
 * newTag: new tag value to be written into file
 */
std::string UpdateTag( std::string l, std::string newTag ) {
    // Check the new tag for validity
    std::string rS = l;

    std::regex rTag{std::string{"(v[0-9]*)(.)([0-9]*)"}};
    if( !std::regex_match(newTag,rTag) ) {
        throw("Incorrect new tag value!");
    }

    // triggers for the line with the tag_ in it, and cut it into pieces    
    std::string reg_tag{"([ ]*[a-zA-Z]*)(.)(tag_ = \")((v[0-9]*)(.)([0-9]*))(\")(.)*"};
    std::regex base_reg{reg_tag};
    std::smatch res;

    if( std::regex_match(l,res,base_reg) ) {
//         std::cout << "found it!" << std::endl;
//         std::cout << "current line is:\n" << l << std::endl;

        rS = std::string{};
        rS+=res.str(1);
        rS+=res.str(2);
        rS+=res.str(3);
        rS+=newTag;
        rS+=res.str(8);
        rS+=res.str(9);

//         std::cout << "New Line should be:\n" << rS << std::endl;

    }
    return rS;
}

/**
 * Finds the line which contain the branch_ value and refresh the whole line
 * l: current line of the file
 * newBranch: new Branch value to be written into file
 */
std::string  UpdateBracnh( std::string l, std::string newBranch ) {
    std::string rS=l;
    // triggers for the line with the branch_ in it, and cut it into pieces    
    std::string reg{"([ ]*[a-zA-Z]*)(.)(branch_ = \")([a-zA-Z0-9]*)(\")(.)*"}; 
    std::regex base_reg{reg};
    std::smatch res;

    if( std::regex_match(l,res,base_reg) ) {
//         std::cout << "found it!" << std::endl;
//         std::cout << "current line is:\n" << l << std::endl;
        rS = std::string{};

        rS+=res.str(1);
        rS+=res.str(2);
        rS+=res.str(3);
        rS+=newBranch;
        rS+=res.str(5);
        rS+=res.str(6);

//         std::cout << "New Line should be:\n" << rS << std::endl;

    }
    return rS;
}

/**
 * Finds the line which contain the buildNum_ value and refresh the whole line
 * f: file pointer
 * l: current line of the file
 * pw: writing pointer of the file - where this function will srite
 * buildNum: new nuild number value to be written into file
 */
std::string UpdateBuilNum( std::string l, std::string buildNum ) {
    std::string rS = l;
    // triggers for the line with the branch_ in it, and cut it into pieces    
    std::string reg{"([ ]*[a-zA-Z]*)(.)(buildNum_ = )([0-9]*)(.)*"};
    std::regex base_reg{reg};
    std::smatch res;

    if( std::regex_match(l,res,base_reg) ) {
//         std::cout << "found it!" << std::endl;
//         std::cout << "current line is:\n" << l << std::endl;

        rS=std::string{};
        rS+= res.str(1);
        rS+= res.str(2);
        rS+= res.str(3);
        rS+= buildNum;
        rS+= res.str(5);

//         std::cout << "New Line should be:\n" << rS << std::endl;
    }
    return rS;
}





int main(int argc, char *argv[] ) {
    std::string buildNum{};

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

    buildNum = std::string{match.str(2)};

    
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

    std::fstream file {"fwid.cpp",std::ios::in };
    std::vector<std::string> tempF{};

    while( std::getline(file,line)) {
        tempF.push_back(line);
    }
    
    file.close();

    // change the data inside the buffer
    for( auto &l : tempF ) {
//         std:: cout << l << std::endl;
        l = UpdateTag(l, std::string{argv[1]});
        l = UpdateBracnh(l, std::string{argv[2]});
        l = UpdateBuilNum(l, buildNum);
    }

//     for( auto l : tempF )
//         std::cout << l << std::endl;

    std::fstream fo {"fwid_temp.cpp", std::ios::out };
    for( auto l: tempF)
        fo << l << std::endl;

    fo.close();

    // invoke system command to replace files
    auto r = system("mv -v ./fwid_temp.cpp ./fwid.cpp");

    if( r ) {
        std::string err{};
        err+="Could not rename the fwid.cpp! Error code: "; 
        err+= std::to_string(r);
        err+="\n";
        throw(err);
    }

    }
    catch(const char* e)  {
        std::cout << e << std::endl;
    }

    return 0;
}
