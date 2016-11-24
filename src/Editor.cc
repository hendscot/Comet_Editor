#include <ncurses.h>
#include "Editor.h"
#include "Document.h"
#include "LineMan.h"

Editor::Editor() {
  e_doc = new Document;
  e_man = new LineMan;
}

Editor::~Editor() {
  delete e_doc;
  delete e_man;
}

void Editor::LoadFile() {
  e_doc->LoadDocument("/home/scotth3n/ClionProjects/Comet_Editor/Comet_Editor/src/test.txt");
  int length = e_doc->GetSize();
  for (int i = 0; i < length; i++){
    e_man->Append(e_doc->buffer[i]);
  }
}

void Editor::SaveFile() {

}

void Editor::Display() {
  e_man->Display();
}
