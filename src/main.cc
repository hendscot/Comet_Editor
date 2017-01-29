#include <iostream>
#include "Editor.h"

int main (int argc, char* argv[]) {
  Comet::Editor* ed = new Comet::Editor();
  ed->Load("./test.txt");
  ed->Run();
  delete ed;
  return 1;
}