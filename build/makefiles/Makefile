GCC   = g++ -std=c++11
DEBUG = -g
SRC   = ../../src/
XCORE = ../../src/Core/
XINT  = ../../src/Interface/
XIO   = ../../src/IO/
ICORE = ../../includes/Core/
IINT  = ../../includes/Interface/
IIO   = ../../includes/IO/
STR   = ../../utils/Comet-String/
OBJ   = ../objects/
EXE   = ../executables/
LINK  = -lncurses

all: main

main: Menu.o LineManager.o Line.o Document.o GhostEditorCore.o GhostEditor.o String.o main.o
	$(GCC) -o $(EXE)main $(OBJ)String.o $(OBJ)Menu.o $(OBJ)LineManager.o $(OBJ)Line.o $(OBJ)Document.o $(OBJ)GhostEditorCore.o $(OBJ)GhostEditor.o $(OBJ)main.o $(LINK)

LineManager.o: $(ICORE)LineManager.h $(XCORE)LineManager.cc
	$(GCC) -c -o $(OBJ)LineManager.o $(XCORE)LineManager.cc

Line.o: $(ICORE)Line.h $(XCORE)Line.cc
	$(GCC) -c -o $(OBJ)Line.o $(XCORE)Line.cc

GhostEditorCore.o: $(ICORE)GhostEditorCore.h $(XCORE)GhostEditorCore.cc
	$(GCC) -c -o $(OBJ)GhostEditorCore.o $(XCORE)GhostEditorCore.cc $(LINK)

Document.o: $(IIO)Document.h $(XIO)Document.cc
	$(GCC) -c -o $(OBJ)Document.o $(XIO)Document.cc

GhostEditor.o: $(IINT)GhostEditor.h $(XINT)GhostEditor.cc
	$(GCC) -c -o $(OBJ)GhostEditor.o $(XINT)GhostEditor.cc $(LINK)

Menu.o: $(IINT)Menu.h $(XINT)Menu.cc
	$(GCC) -c -o $(OBJ)Menu.o $(XINT)Menu.cc $(Link)

String.o: $(STR)String.cc $(STR)String.h
	$(GCC) -c -o $(OBJ)String.o $(STR)String.cc

main.o: $(SRC)main.cc
	$(GCC) -c -o $(OBJ)main.o $(SRC)main.cc

clean:
	rm ../objects/*o
