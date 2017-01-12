#include "Editor.h"
#include "Document.h"
#include "LineMan.h"
#include <ncurses.h>
#include <iostream>

Editor::Editor(char* pathname) {
  initscr        ();
  cbreak         ();
  noecho         ();
  keypad         (stdscr, true);
  e_doc          = new Document;
  e_man          = new LineMan;
  e_path         = pathname;
  e_shouldClose  = false;
  e_currLine     = 0;
  e_row          = 0;
  e_col          = 0;
  this->LoadFile ();
  this->Display();
  move(e_row, e_col);
}

Editor::~Editor() {
  delete e_doc;
  delete e_man;
  endwin();
}

void Editor::LoadFile() {
  e_doc->LoadDocument(e_path);
  int length = e_doc->GetSize();
  for (int i = 0; i < length; i++){
	   e_man->Append(e_doc->buffer[i]);
  }
}

void Editor::SaveFile() {

}

void Editor::Display() {
  e_man->Display();
  refresh();
}


void Editor::Update() {
  e_key = getch();
  switch (e_key) {
    case KEY_UP: {
      if (e_currLine > 0) ++e_currLine;
      move (--e_row, e_col);
      break;
    }
    case KEY_DOWN: {
      ++e_currLine;
      move (++e_row, e_col);
      break;
    }
    case KEY_RIGHT: {
      move (e_row, ++e_col);
      break;
    }
    case KEY_LEFT: {
      move (e_row, --e_col);
      break;
    }
    case KEY_DC: {
      e_man->DeleteChar(e_currLine, e_col);
      clear();
      this->Display();
      move (e_row, --e_col);
    }
    default: {
      e_man->InsertChar(e_currLine, e_col, e_key);
      clear();
      this->Display();
      move (e_row, ++e_col);
      break;
    }
  }

}

void Editor::Delete(int ln, int in) {
	e_man->DeleteChar(e_currLine, in);
}

bool Editor::ShouldClose() {
  if (e_shouldClose) {
    return 1;
  }
  else {
    return 0;
  }
}
