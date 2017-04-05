/************************************************
COMET GHOST TEXT EDITOR Ver. 0.0.1
Written by: Scott Henderson
Last Update: Jan 31 2017
*************************************************/
#include <iostream>
#include "Editor.h"

int main (int argc, char* argv[]) {
  Comet::Editor* ed = new Comet::Editor();
  ed->Load(argv[1]);
  ed->Run();
  delete ed;
  return 1;
}