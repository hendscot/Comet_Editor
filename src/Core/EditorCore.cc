#include <ncurses.h>
#include "../../utils/Comet-String/String.h"
#include "../../includes/Core/EditorCore.h"
#include "../../includes/Core/LineManager.h"
#include "../../includes/IO/Document.h"
namespace Ghost {
  namespace Core {
    EditorCore::EditorCore()
    : shouldClose_(0), currLine_(0),
      currIndex_(LINE_OFFSET) {
      lines_ = new LineManager;
      this->InitGUIOptions   ();
    } // EDITOR (CHAR*)

    // Deconstruct Editor
    EditorCore::~EditorCore() {
      delete lines_;
      endwin();
    } // ~EDITOR ()

    // Initialize ncurses DisplayToTerminal options
    void EditorCore::InitGuiOptions () {
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

    void EditorCore::Poll () {
        HandleKeyInput ();
    }

    void EditorCore::Load (const char* filepath) {
      path_ = filepath;
      Ghost::IO::Document::LoadDocument(path_);
      int length = Ghost::IO::Document::GetSize();
      String str(Ghost::IO::Document::GetBuffer());
      Ghost::IO::Document::CleanUp();
      for (int i = 0; i < length; i++){ 
        lines_->Append(str[i]);
      }
      this->DisplayToTerminal ();
      move (0, LINE_OFFSET);
    }

    void EditorCore::Save () {
      Ghost::IO::Document::SaveDocument(path_, lines_->GetStart());
    }

    // Method to acquire and handle user input
    void EditorCore::HandleKeyInput () {
      key_ = getch();                               
      switch (key_) {
        case UP: {
          CursorUp ();
          break;
        }
        case DOWN: {
          CursorDown ();
          break;
        }
        case LEFT: {
          CursorLeft ();
          break;
        }
        case RIGHT: {
          CursorRight ();
          break;
        }
        case TAB: {
          InsertTab ();
          break;
        }
        case BACKSPACE: {
          RemoveCharacter ();
          break;
        }
        case ENTER: {
          InsertNewline ();
          break;
        }
        case SAVE: {
          Save();
          break;
        }
        default: {
          InsertCharacter ();
          break;
        }
      }
    } // HandleKeyInput ()

      // Delete current index of current line TODO
    void EditorCore::Delete (int ln, int in) {
      lines_->DeleteChar(ln, (in - LINE_OFFSET));
    } // DELETE (INT, INT)

    void EditorCore::Insert (int line, int indx, char ch) {
      lines_->InsertChar(line, (indx - LINE_OFFSET), ch);
    }

    void EditorCore::DisplayToTerminal () {
      clear ();
      lines_->Display();
      refresh ();
    } // DisplayToTerminal ()

    void EditorCore::CursorUp () {
        if (currLine_ > 0) {
        if ((lines_->GetLength(currLine_ - 1) + LINE_OFFSET) < currIndex_) {
         move (currLine_ -= 1, currIndex_ = (lines_->GetLength(currLine_ - 1) + LINE_OFFSET));
        }
        else {
          move (--currLine_, currIndex_);
        }
      }
    }

    void EditorCore::CursorDown () {
        if ((currLine_ + 1) < lines_->GetLineCount ()) {
        if (currIndex_ >= lines_->GetLength(currLine_ + 1) + LINE_OFFSET) {
          move (++currLine_, (currIndex_ = (lines_->GetLength(currLine_ + 1) + LINE_OFFSET)));          // move cursor down one line
        }
        else {
          move (++currLine_, currIndex_);
        }
      }
    }

    void EditorCore::CursorLeft () {
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

    void EditorCore::CursorRight () {
      if ((currIndex_) < lines_->GetLength(currLine_) + LINE_OFFSET) {
        move (currLine_, ++currIndex_);
      }
      else {
        if ((currLine_ + 1) < (lines_->GetLineCount())) {
          move (++currLine_, currIndex_ = LINE_OFFSET);
        }
      }
    }

    void EditorCore::RemoveCharacter () {
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

    void EditorCore::InsertCharacter () {
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

    void EditorCore::InsertNewline () {
      lines_->InsertBreak(currLine_, currIndex_ - LINE_OFFSET);
      this->DisplayToTerminal();
      move (++currLine_, (currIndex_ = LINE_OFFSET));
    }

    void EditorCore::InsertTab () {
      if (currIndex_ < lines_->GetLength(currLine_) + LINE_OFFSET) {
        for (int i = 0; i < TAB_SIZE; i++) {
          Insert(currLine_, currIndex_++, E_SPACE);
        }
      }
      else {
        for (int i = 0; i < TAB_SIZE; i++) {
          lines_->Append(E_SPACE, currLine_);
          ++currIndex_;
        }
      }
      this->DisplayToTerminal();
      move (currLine_, currIndex_);
    }
  }
}
