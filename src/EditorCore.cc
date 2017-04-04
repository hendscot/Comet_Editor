#include <ncurses.h>
#include "String.h"
#include "EditorCore.h"
namespace Comet {
  namespace Core {
    EditorCore::EditorCore()
    : e_shouldClose(0), e_currLine(0)
      e_currIndex(E_BEG), e_man = new LineManager {
      this->InitGUIOptions   ();                         // Initalize members and ncurses
    } // EDITOR (CHAR*)

    // Deconstruct Editor
    EditorCore::~EditorCore() {
      delete e_man;                                  // Delete editor object
      endwin();                                      // clean up ncurses
    } // ~EDITOR ()

        // Initialize members and ncurses
    void EditorCore::InitGUIOptions () {
      initscr             ();                         // initialize ncurses!
      cbreak              ();                         //
      noecho              ();                         // disable ncurses key echo
      keypad              (stdscr, true);             // enable ncurses special keys
      start_color();
      init_pair(1, COLOR_GREEN, COLOR_BLACK);
      attron(COLOR_PAIR(1));
    } // INIT ()

    void EditorCore::Poll () {
        HandleInput ();
    }

    void EditorCore::Load (const char* filepath) {
      e_path = filepath;
      Comet::IO::Document::LoadDocument(e_path);                   // Load contents of file at e_path into Document buffer
      int length = Comet::IO::Document::GetSize();                 // store the length of the file buffer
      String str(Comet::IO::Document::GetBuffer());
      Comet::IO::Document::CleanUp();
      for (int i = 0; i < length; i++){              // transfer buffer contents into lines in the line manager object
        e_man->Append(str[i]);
      }
      this->Display ();
      move (0, E_BEG);
    }

    void EditorCore::Save () {
      Comet::IO::Document::SaveDocument(e_man->GetStart());
    }

  // Method to acquire and handle user input
    void EditorCore::HandleInput () {
      e_key = getch();                               // store value of key E_ENTERed by user in e_key var
      switch (e_key) {                               // handle input based on value defined by ncurses
        case KEY_UP: {                               // if up arrow key
          if (e_currLine > 0) {                      // move cursor up one line if not yet on first line
              if ((e_man->GetLength(e_currLine - 1) + E_BEG) < e_currIndex) {
                  move (e_currLine -= 1, e_currIndex = (e_man->GetLength(e_currLine - 1) + E_BEG));
              }
              else {
                  move (--e_currLine, e_currIndex);
              }
          }
          break;
        }
        case KEY_DOWN: {                             // if down arrow key
          if ((e_currLine + 1) < e_man->GetLineCount () - 1) {
              if (e_currIndex >= e_man->GetLength(e_currLine + 1) + E_BEG) {
                  move (++e_currLine, (e_currIndex = (e_man->GetLength(e_currLine + 1) + E_BEG)));          // move cursor down one line
              }
              else {
                  move (++e_currLine, e_currIndex);
              }
          }
          break;
        }
        case E_TAB: {
          if (e_currIndex < e_man->GetLength(e_currLine) + E_BEG) {
            for (int i = 0; i < E_TAB_SIZE; i++) {
              Insert(e_currLine, e_currIndex++, E_SPACE);
            }
          }
          else {
            for (int i = 0; i < E_TAB_SIZE; i++) {
              // TODO FIND WAY TO FIX INSERT TO REMOVE APPEND
              e_man->Append(E_SPACE, e_currLine);
              ++e_currIndex;
            }
          }
          this->Display();
          move (e_currLine, e_currIndex);
          break;
        }
        case KEY_RIGHT: {                            // if right arrow key
          if ((e_currIndex) < e_man->GetLength(e_currLine) + E_BEG) {
            move (e_currLine, ++e_currIndex);          // move cursor right one index
          }
          else {
            if ((e_currLine + 1) < (e_man->GetLineCount() - 1)) move (++e_currLine, e_currIndex = E_BEG);
          }
          break;
        }
        case KEY_LEFT: {
          if (e_currLine > 0) {                         // if left arrow key
            if (e_currIndex > E_BEG) {
              move (e_currLine, --e_currIndex);          // move cursor left one index
            }
            else {
              move (--e_currLine, e_currIndex = (e_man->GetLength(e_currLine - 1) + E_BEG));
            }
          }
          else {
            if (e_currIndex > E_BEG) {
              move (e_currLine, --e_currIndex);          // move cursor left one index
            }          
          }
          break;
        }
        case KEY_BACKSPACE: {
          if ((e_currIndex) > E_BEG) {
            Delete(e_currLine, e_currIndex);
            this->Display();
            move (e_currLine, (--e_currIndex));

          }
          else if (e_currIndex == E_BEG && e_currLine > 0) {
              int oldlength = (e_man->GetLength(e_currLine - 1) + E_BEG);
              Delete(e_currLine, e_currIndex);
              this->Display();
              move (--e_currLine, (e_currIndex = oldlength));
          }
          break;
        }
        case E_ENTER: {
          e_man->InsertBreak(e_currLine, e_currIndex - E_BEG);
          this->Display();
          move (++e_currLine, (e_currIndex = E_BEG));
          break;
        }
        case KEY_SLEFT: {
          Save();
          break;
        }
        default: {                                             // if letter TODO: specify if alpha char
          if (e_currIndex < (e_man->GetLength(e_currLine) + E_BEG)) {
            Insert(e_currLine, e_currIndex, e_key);   // insert char at current cursor line and index
            this->Display();                                     // update state of ncurses windows
            move (e_currLine, e_currIndex += 1);                    // move cursor to next index
          }
          else {
            e_man->Append(e_key, e_currLine);
            this->Display();
            move (e_currLine, e_currIndex += 1);
          }
          break;
        }
      }
    } // HANDLEINPUT ()

      // Delete current index of current line TODO
    void EditorCore::Delete (int ln, int in) {
      e_man->DeleteChar(ln, (in - E_BEG));
    } // DELETE (INT, INT)

    void EditorCore::Insert (int line, int indx, char ch) {
      e_man->InsertChar(line, (indx - E_BEG), ch);
    }

      void EditorCore::Display () {
        clear ();
        e_man->Display();
        refresh ();
    } // DISPLAY ()
  } 
}
