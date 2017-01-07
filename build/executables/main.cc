#include <iostream>
#include "Editor.h"
#include "LineMan.h"
#include "Document.h"

int main (int argc, char* argv[]) {
  Editor* ed = new Editor();
  ed->LoadFile();
  ed->Display();
  ed->Delete(0);
  ed->Display();
  std::cin.get();
  return 1;
}
