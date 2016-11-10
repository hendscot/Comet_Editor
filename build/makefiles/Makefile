GCC = g++
SRC = ../../src/
UTILS = ../../utils/
OBJ = ../objects/
EXE = ../executables/

all: main

main: FileHandler.o LineMan.o Line.o Document.o main.o
	$(GCC) -o $(EXE)main $(OBJ)FileHandler.o $(OBJ)LineMan.o $(OBJ)Line.o $(OBJ)Document.o $(OBJ)main.o

FileHandler.o: $(UTILS)FileHandler.cc $(UTILS)FileHandler.h
	$(GCC) -c -o $(OBJ)FileHandler.o $(UTILS)FileHandler.cc

LineMan.o: $(SRC)LineMan.h $(SRC)LineMan.cc
	$(GCC) -c -o $(OBJ)LineMan.o $(SRC)LineMan.cc

Line.o: $(SRC)Line.h $(SRC)Line.cc
	$(GCC) -c -o $(OBJ)Line.o $(SRC)Line.cc

Document.o: $(SRC)Document.h $(SRC)Document.cc
	$(GCC) -c -o $(OBJ)Document.o $(SRC)Document.cc

main.o: $(SRC)main.cc
	$(GCC) -c -o $(OBJ)main.o $(SRC)main.cc

clean:
	rm ../objects/*o
