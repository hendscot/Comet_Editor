#include "EditorCore.h"
#include "Menu.h"
#include <ncurses.h>
namespace Comet {

  EditorCore::EditorCore() {
    this->Init         ();                         // Initalize members and ncurses
  } // EDITOR (CHAR*)

  // Deconstruct Editor
  EditorCore::~EditorCore() {
    delete e_doc;                                  // Delete document object
    delete e_man;                                  // Delete editor object
    endwin();                                      // clean up ncurses
  } // ~EDITOR ()

      // Initialize members and ncurses
  void EditorCore::Init () {
    initscr             ();                         // initialize ncurses!
    cbreak              ();                         // 
    noecho              ();                         // disable ncurses key echo
    keypad              (stdscr, true);             // enable ncurses special keys
    e_doc              = new Document;             // Create new document object
    e_man              = new LineManager;          // create new LineMan object
    e_shouldClose      = false;                    // set shouldClose state to false
    e_currLine         = 0;                        // default line is 0
    e_currIndex        = 0;                        // default index is 0
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));
  } // INIT ()

  void EditorCore::Poll () {
      HandleInput ();
  }

  void EditorCore::Load (const char* filepath) {
    e_path = filepath;
    e_doc->LoadDocument(e_path);                   // Load contents of file at e_path into Document buffer
    int length = e_doc->GetSize();                 // store the length of the file buffer
    for (int i = 0; i < length; i++){              // transfer buffer contents into lines in the line manager object
      e_man->Append(e_doc->buffer[i]);
    }
    this->Display ();
    move (0, 0);
  }

  void EditorCore::Save () {
  }

 // Method to acquire and handle user input
  void EditorCore::HandleInput () {
    e_key = getch();                               // store value of key entered by user in e_key var
    switch (e_key) {                               // handle input based on value defined by ncurses
      case KEY_UP: {                               // if up arrow key
        if (e_currLine > 0) {                      // move cursor up one line if not yet on first line
            if ((e_currIndex) > e_man->GetLength(e_currLine - 1)) {
                move (--e_currLine, (e_currIndex = (e_man->GetLength(e_currLine + 1))));
            }
            else {
                move (--e_currLine, e_currIndex);
            }
        }
        break;
      }
      case KEY_DOWN: {                             // if down arrow key
        if ((e_currLine + 1) < e_man->GetLineCount () - 1) {
            if (e_currIndex >= e_man->GetLength(e_currLine + 1)) {
                move (++e_currLine, (e_currIndex = (e_man->GetLength(e_currLine + 1))));          // move cursor down one line
            }
        
            else {
                move (++e_currLine, e_currIndex);
            }
        }
        break;
      }
      case KEY_RIGHT: {                            // if right arrow key
        if ((e_currIndex) < e_man->GetLength(e_currLine)) {
          move (e_currLine, ++e_currIndex);          // move cursor right one index
        }
        break;
      }
      case KEY_LEFT: {   
        if (e_currIndex > 0)                          // if left arrow key
          move (e_currLine, --e_currIndex);          // move cursor left one index
        break;
      }
      case KEY_BACKSPACE: {                               
        if ((e_currIndex) > 0) {
          Delete(e_currLine, e_currIndex);
          this->Display();
          move (e_currLine, (--e_currIndex)); 
            
        }
        else if (e_currIndex == 0 && e_currLine > 0) {
            Delete(e_currLine, e_currIndex);
            this->Display();
            move (--e_currLine, (e_currIndex = (e_man->GetLength(e_currLine - 1))));
        }
            
        break;
      }
      case ENTER: {
        e_man->InsertBreak(e_currLine, e_currIndex, e_key);
        this->Display();
        move (++e_currLine, (e_currIndex = 0));
        break;
      }
      case KEY_SLEFT: {
        Save();     
        break;
      }
      default: {                                             // if letter TODO: specify if alpha char
        if (e_currIndex < e_man->GetLength(e_currLine)) {
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

    // Delete current index of current liner TODO
  void EditorCore::Delete (int ln, int in) {
    e_man->DeleteChar(ln, in);
  } // DELETE (INT, INT)

  void EditorCore::Insert (int line, int indx, char ch) {
    e_man->InsertChar(line, indx, ch);
  }

    void EditorCore::Display () {
      clear ();
      if (l_strt){
        LPTR l_iter = e_man->First();
        do {
          // test if this will work?
          printw(l_iter->str->GetBuff());
          printw("\n");
          l_iter = l_iter->next;
        } while (l_iter != l_strt && l_iter != NULL);
      }
      refresh ();
	} // DISPLAY ()
}
