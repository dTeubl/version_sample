# Make file for the RegExp Projet - II. Homework of the c++11 programing course.
SHELL = /bin/bash

# Local variables
CC = g++
CFLAGS = -std=c++17 -Wall -Weffc++ -time -Wdeprecated -pedantic
PROG = genver

SRC = getver.cpp 
HEADERS = 
OBJS = getver.o

# Rules to generate the program

$(PROG):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ 
	make clean

# Rules to clean up the project

clean:
	rm -f *.o *.log	

# rules to generate *.o files
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# rules for the fwid sample program

fwid.o: fwid.h

.PHONY: fwid
fwid: fwid.o
	${CC} ${CFLAGS} $^ -o $@


