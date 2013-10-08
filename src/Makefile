#
# Main makefile for the Slot Machine project
# @author : Pascal Marechal <paskal.marechal@gmail.com>
# Date : 04/10/2013
#

CC = g++

CFLAGS = -W -Wall -ansi -pedantic -o2
#CFLAGS = -g 				#for DEBUG only

EXEC = ../bin/slotmachine

SRC = $(shell find . -name "*.cpp")

OBJS = $(SRC:%.cpp=%.o)

SUBDIRS = Symbols

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

all : $(EXEC)

clean : 
	rm -rf $(OBJS) \
	rm *~ \
	rm $(EXEC)

$(EXEC) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)


.PHONY: clean


