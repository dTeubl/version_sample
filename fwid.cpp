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
#include "fwid.h"


FWID gFwID;

void InitFwID( void ) {
    gFwID.tag_ = "v1.3";
    gFwID.branch_ = "master";
    gFwID.buildNum_ = 17;
}

int main( ) {
    InitFwID( );

    std::cout << "Firware properties:\n";
    std::cout << "Tag:\t" << gFwID.tag_ << std::endl;
    std::cout << "Branch:\t" << gFwID.branch_ << std::endl;
    std::cout << "BuildNum:\t" << gFwID.buildNum_ << std::endl;

    return 0;
}
