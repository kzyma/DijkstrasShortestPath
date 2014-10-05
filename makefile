######################################################
#
# File: makefile
# Author: Ken Zyma
#
######################################################

FLAGS = -std=c++11

all: build

build: shortest clean

shortest: graph.o paths.o
	g++ $(FLAGS) -o shortest shortest.cpp graph.o paths.o

graph.o:
	g++ $(FLAGS) -c graph.cpp

paths.o:
	g++ $(FLAGS) -c paths.cpp

clean:
	rm -rf *.o;
