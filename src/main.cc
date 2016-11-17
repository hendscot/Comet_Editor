#include <iostream>
#include "Editor.h"
#include "LineMan.h"
#include "Document.h"

int main (int argc, char* argv[]) {
  Editor* ed = new Editor("helloworld.cc");
  ed->Display();
  //LineMan* lm = new LineMan;
  //lm->Display();
  return 1;
}
