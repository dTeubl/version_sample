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
#ifndef _FWID_H_
#define _FWID_H_

#include <iostream>

 
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

extern FWID gFwID;

void InitFwID( void );

#endif /* _FWID_H_ */

