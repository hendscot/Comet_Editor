#include <ncurses.h>
#include "../../utils/Comet-String/String.h"
#include "../../includes/Core/GhostEditorCore.h"
#include "../../includes/Core/LineManager.h"
#include "../../includes/IO/Document.h"
using namespace Ghost;
using namespace Core;
GhostEditorCore::GhostEditorCore()
    : shouldClose_(0), currLine_(0),
      currIndex_(LINE_OFFSET + 1) {
      lines_ = new LineManager;
      this->InitGuiOptions   ();
}
GhostEditorCore::~GhostEditorCore() {
  delete lines_;
  endwin();
}

// Initialize ncurses DisplayToTerminal options
void
GhostEditorCore::InitGuiOptions () {
  // setup screen
  initscr             ();
  // no buffer!
  cbreak              ();
  noecho              ();
  // we want special keys in main window
  keypad              (stdscr, true);
  // all output will be green text on black background
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  attron(COLOR_PAIR(1));
} // INIT ()

void GhostEditorCore::Poll () {
  HandleKeyInput ();
}

void
GhostEditorCore::Load (const char* filepath) {
  path_ = filepath;
  Ghost::IO::Document::LoadDocument(path_);
  int length = Ghost::IO::Document::GetSize();
  Comet::String str(Ghost::IO::Document::GetBuffer());
  Ghost::IO::Document::CleanUp();
  for (int i = 0; i < length; i++){
      lines_->Append(str[i]);
  }
  this->DisplayToTerminal ();
  move (0, LINE_OFFSET);
}

void
GhostEditorCore::Save () {
  Ghost::IO::Document::SaveDocument(path_, lines_->GetStart());
}

// Method to acquire and handle user input
void
GhostEditorCore::HandleKeyInput () {
  key_ = getch();
  switch (key_) {
    case KEY_UP: {
      MoveCursorUp ();
      break;
    }
    case KEY_DOWN: {
      MoveCursorDown ();
      break;
    }
    case KEY_LEFT: {
      MoveCursorLeft ();
      break;
    }
    case KEY_RIGHT: {
      MoveCursorRight ();
      break;
    }
    case TAB: {
      InsertTab ();
      break;
    }
    case KEY_BACKSPACE: {
      RemoveCharacter ();
      break;
    }
    case ENTER: {
      InsertNewline ();
      break;
    }
    case KEY_SLEFT: {
      Save();
      break;
    }
    default: {
      InsertCharacter ();
      break;
    }
  }
}

// Delete current index of current line TODO
void
GhostEditorCore::Delete (int ln, int in) {
  lines_->DeleteChar(ln, (in - LINE_OFFSET));
}

void
GhostEditorCore::Insert (int line, int indx, char ch) {
  lines_->InsertChar(line, (indx - LINE_OFFSET), ch);
}

void
GhostEditorCore::DisplayToTerminal () {
  clear ();
  lines_->Display();
  refresh ();
}

void
GhostEditorCore::MoveCursorUp () {
  if (currLine_ > 0) {
    if ((lines_->GetLength(currLine_ - 1) + LINE_OFFSET) < currIndex_) {
      move (currLine_ -= 1, currIndex_ = (lines_->GetLength(currLine_ - 1) + LINE_OFFSET));
    }
    else {
      move (--currLine_, currIndex_);
    }
  }
}

void
GhostEditorCore::MoveCursorDown () {
  if ((currLine_ + 1) < lines_->GetLineCount ()) {
    if (currIndex_ >= lines_->GetLength(currLine_ + 1) + LINE_OFFSET) {
      move (++currLine_, (currIndex_ = (lines_->GetLength(currLine_ + 1) + LINE_OFFSET)));          // move cursor down one line
    }
    else {
      move (++currLine_, currIndex_);
    }
  }
}

void
GhostEditorCore::MoveCursorLeft () {
  if (currLine_ > 0) {
    if (currIndex_ > LINE_OFFSET) {
      move (currLine_, --currIndex_);
    }
    else {
      move (--currLine_, currIndex_ = (lines_->GetLength(currLine_ - 1) + LINE_OFFSET));
    }
  }
  else {
    if (currIndex_ > LINE_OFFSET) {
      move (currLine_, --currIndex_);
    }
  }
}

void
GhostEditorCore::MoveCursorRight () {
  if ((currIndex_) < lines_->GetLength(currLine_) + LINE_OFFSET) {
    move (currLine_, ++currIndex_);
  }
  else {
    if ((currLine_ + 1) < (lines_->GetLineCount())) {
      move (++currLine_, currIndex_ = LINE_OFFSET);
    }
  }
}

void
GhostEditorCore::RemoveCharacter () {
  if ((currIndex_) > LINE_OFFSET) {
    Delete(currLine_, currIndex_);
    this->DisplayToTerminal();
    move (currLine_, (--currIndex_));
  }
  else if (currIndex_ == LINE_OFFSET && currLine_ > 0) {
    int oldlength = (lines_->GetLength(currLine_ - 1) + LINE_OFFSET);
    Delete(currLine_, currIndex_);
    this->DisplayToTerminal();
    move (--currLine_, (currIndex_ = oldlength));
  }
}

void
GhostEditorCore::InsertCharacter () {
  if (currIndex_ < (lines_->GetLength(currLine_) + LINE_OFFSET)) {
    Insert(currLine_, currIndex_, key_);
    this->DisplayToTerminal();
    move (currLine_, currIndex_ += 1);
  }
  else {
    lines_->Append(key_, currLine_);
    this->DisplayToTerminal();
    move (currLine_, currIndex_ += 1);
  }
}

void
GhostEditorCore::InsertNewline () {
  lines_->InsertBreak(currLine_, currIndex_ - LINE_OFFSET);
  this->DisplayToTerminal();
  move (++currLine_, (currIndex_ = LINE_OFFSET));
}

void
GhostEditorCore::InsertTab () {
  if (currIndex_ < lines_->GetLength(currLine_) + LINE_OFFSET) {
    for (int i = 0; i < TAB_SIZE; i++) {
      Insert(currLine_, currIndex_++, SPACE);
    }
  }
  else {
    for (int i = 0; i < TAB_SIZE; i++) {
      lines_->Append(SPACE, currLine_);
      ++currIndex_;
    }
  }
  this->DisplayToTerminal();
  move (currLine_, currIndex_);
}