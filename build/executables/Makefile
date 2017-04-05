GCC = g++ -std=c++11
SRC = ../../src/
UTILS = ../../utils/
STR   = ../../utils/Comet-String/
OBJ = ../objects/
EXE = ../executables/
LINK = -lncurses

all: main

main: Menu.o LineManager.o Line.o Document.o EditorCore.o Editor.o String.o main.o
	$(GCC) -o $(EXE)main $(OBJ)String.o $(OBJ)Menu.o $(OBJ)LineManager.o $(OBJ)Line.o $(OBJ)Document.o $(OBJ)EditorCore.o $(OBJ)Editor.o $(OBJ)main.o $(LINK)

LineManager.o: $(SRC)LineManager.h $(SRC)LineManager.cc
	$(GCC) -c -o $(OBJ)LineManager.o $(SRC)LineManager.cc

Line.o: $(SRC)Line.h $(SRC)Line.cc
	$(GCC) -c -o $(OBJ)Line.o $(SRC)Line.cc

Document.o: $(SRC)Document.h $(SRC)Document.cc
	$(GCC) -c -o $(OBJ)Document.o $(SRC)Document.cc

EditorCore.o: $(SRC)EditorCore.h $(SRC)EditorCore.cc
	$(GCC) -c -o $(OBJ)EditorCore.o $(SRC)EditorCore.cc $(LINK)

Editor.o: $(SRC)Editor.h $(SRC)Editor.cc
	$(GCC) -c -o $(OBJ)Editor.o $(SRC)Editor.cc $(LINK)

Menu.o: $(SRC)Menu.h $(SRC)Menu.cc
	$(GCC) -c -o $(OBJ)Menu.o $(SRC)Menu.cc $(Link)

String.o: $(STR)String.cc $(STR)String.h
	$(GCC) -c -o $(OBJ)String.o $(STR)String.cc

main.o: $(SRC)main.cc
	$(GCC) -c -o $(OBJ)main.o $(SRC)main.cc

clean:
	rm ../objects/*o
