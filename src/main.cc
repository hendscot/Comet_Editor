/************************************************
COMET GHOST TEXT EDITOR Ver. 0.3.1
Written by: Scott Henderson
*************************************************/
#include <iostream>
#include "../includes/Interface/Editor.h"

int main (int argc, char* argv[]) {
  Ghost::Interface::Editor* ed = new Ghost::Interface::Editor();
  ed->Load(argv[1]);
  ed->Run();
  delete ed;
  return 1;
}
