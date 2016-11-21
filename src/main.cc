#include <iostream>
#include "Editor.h"
#include "LineMan.h"
#include "Document.h"

int main (int argc, char* argv[]) {
  Editor* ed = new Editor();
  ed->LoadFile();
  ed->Display();
  /*LineMan* lm = new LineMan;
  for (int i = 0; i < 500; i++){
    lm->Append('a');
  }
  lm->Display();*/
  return 1;
}
