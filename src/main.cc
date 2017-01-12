#include <iostream>
#include "Editor.h"
#include "LineMan.h"
#include "Document.h"

int main (int argc, char* argv[]) {
  Comet::Editor* ed = new Comet::Editor(argv[1]);
  ed->Run();
  delete ed;
  return 1;
}
