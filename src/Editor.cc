#include "Editor.h"
#include "Document.h"
#include "LineMan.h"
#include <iostream>

Editor::Editor() {
  e_doc = new Document;
  e_man = new LineMan;
  currLine = 0;
}

Editor::~Editor() {
  delete e_doc;
  delete e_man;
}

void Editor::LoadFile() {
  e_doc->LoadDocument("C:/Users/scott/Documents/Visual Studio 2013/Projects/Project9/test.txt");
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

void Editor::Delete(unsigned in) {
	e_man->Delete(currLine, in);
}
