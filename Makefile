# Make file for the RegExp Projet - II. Homework of the c++11 programing course.
SHELL = /bin/bash

# Local variables
GXX = g++
CFLAGS = -std=c++17 -Wall -Weffc++ -time -Wdeprecated -pedantic
PROG = genver

SRC = getver.cpp 
HEADERS = 
OBJS = getver.o

# Rules to generate the program

$(PROG):$(OBJS)
	$(GXX) $(CFLAGS) $^ -o $@ 
	make clean

# Rules to clean up the project

.PHONY: clean
clean:
	rm -f *.o *.log	

# rules to generate *.o files
%.o: %.cpp $(HEADERS)
	$(GXX) $(CFLAGS) -c $< -o $@

# rules for the fwid sample program

fwid.o: fwid.h

.PHONY: fwid
fwid: fwid.o
	${GXX} ${CFLAGS} $^ -o $@
	make clean

.PHONY: info
info:
	@echo "Informations about this Makefile:"


