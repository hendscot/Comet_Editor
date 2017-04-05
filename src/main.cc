/************************************************
COMET GHOST TEXT EDITOR Ver. 0.3.1
Written by: Scott Henderson
*************************************************/
#include <iostream>
#include "../includes/Interface/Editor.h"

int main (int argc, char* argv[]) {
  Comet::Editor* ed = new Comet::Editor();
  ed->Load(argv[1]);
  ed->Run();
  delete ed;
  return 1;
}