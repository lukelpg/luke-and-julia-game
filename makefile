CXX=g++
CXXFLAGS=-std=c++20 -Wall -g -MMD
EXEC=luke_game
CCFILES=$(wildcard $(shell find . -name "*.cpp"))
OBJECTS=${CCFILES:.cc=.o}
DEPENDS=${CCFILES:.cc=.d}
NUM_THREADS = 8
MAKEFLAGS = -j$(NUM_THREADS)

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
