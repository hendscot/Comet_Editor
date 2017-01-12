#include <iostream>
#include "Editor.h"
#include "LineMan.h"
#include "Document.h"

int main (int argc, char* argv[]) {
  Editor* ed = new Editor(argv[1]);
  while (!ed->ShouldClose()) {
    ed->Update();
  }
  delete ed;
  return 1;
}
