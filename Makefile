# Makefile for sudoku
# Author: Ankur Dahal
# Date: 05/05/2020

# Compiler and compiler flags
CXX = 		clang++
CXXFLAGS = 	-g3 -std=c++11 -Wall -Wextra -g3 
LDFLAGS = 	-g3

# Note: $@ = name of target
#		$^ = all the dependencies
#		$< = the first dependency
sudoku: sudoku.o
	${CXX} ${LDFLAGS} -o $@ $^

sudoku.o: sudoku.cpp

clean:
	rm -rf sudoku *.dSYM *.o