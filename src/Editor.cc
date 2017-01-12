#include "Editor.h"
#include "Document.h"
#include "LineMan.h"
#include <ncurses.h>
#include <iostream>
// BEGIN NAMESPACE COMET
namespace Comet {
  // Constructing a new Editor with a known pathname
  Editor::Editor(char* pathname) {
    this->Init         ();                         // Initalize members and ncurses
    this->LoadFile     ();                         // Load file into editor
    this->Display      ();                         // print initial state of file to ncurses window
    move               (e_currLine, e_currIndex);  // move ncurses cursor to default location
  } // EDITOR (CHAR*)

  // Deconstruct Editor
  Editor::~Editor() {
    delete e_doc;                                  // Delete document object
    delete e_man;                                  // Delete editor object
    endwin();                                      // clean up ncurses
  } // ~EDITOR ()

  // Initialize members and ncurses
  void Editor::Init () {
    initscr            ();                         // initialize ncurses!
    cbreak             ();                         // 
    noecho             ();                         // disable ncurses key echo
    keypad             (stdscr, true);             // enable ncurses special keys
    e_doc              = new Document;             // Create new document object
    e_man              = new LineMan;              // create new LineMan object
    e_path             = pathname;                 // initialize e_path with pathname of desired file
    e_shouldClose      = false;                    // set shouldClose state to false
    e_currLine         = 0;                        // default line is 0
    e_currIndex        = 0;                        // default index is 0
  } // INIT ()

  // Load file into document buffer && line manager
  void Editor::LoadFile() {
    e_doc->LoadDocument(e_path);                   // Load contents of file at e_path into Document buffer
    int length = e_doc->GetSize();                 // store the length of the file buffer
    for (int i = 0; i < length; i++){              // transfer buffer contents into lines in the line manager object
      e_man->Append(e_doc->buffer[i]);
    }
  } // LOADFILE ()

  // Write contents of editor to file
  void Editor::SaveFile() {
    e_doc->SaveDocument(e_path);                   // TODO: TEST
  } // SAVEFILE ()

  // Call line manager display function to write contents of document to ncurses
  void Editor::Display() {
    e_man->Display();                              // write contents to ncurses window
  } // DISPLAY ()

  // Editor main system loop
  void Editor::Run() {
    while (!this->ShouldClose()) {                 // run actions while state is good
      refresh();                                   // update contents to screen
      this->Update();                              // run update method to get input etc...
    }
  } // RUN ()

  // methods to be run within main system loop
  void Editor::Update() {
    HandleInput();                                 // call method to acquire and handle user input
  } // UPDATE ()

  // Method to acquire and handle user input
  void Editor::HandleInput() {
    e_key = getch();                               // store value of key entered by user in e_key var
    switch (e_key) {                               // handle input based on value defined by ncurses
      case KEY_UP: {                               // if up arrow key
        if (e_currLine > 0) {                      // move cursor up one line if not yet on first line
          move (--e_currLine, e_currIndex);
        }
        break;
      }
      case KEY_DOWN: {                             // if down arrow key
        move (++e_currLine, e_currIndex);          // move cursor down one line
        break;
      }
      case KEY_RIGHT: {                            // if right arrow key
        move (e_currLine, ++e_currIndex);          // move cursor right one index
        break;
      }
      case KEY_LEFT: {                             // if left arrow key
        move (e_currLine, --e_currIndex);          // move cursor left one index
        break;
      }
      case KEY_DC: {                               // TODO
        e_man->DeleteChar(e_currLine, e_currIndex);
        clear();
        this->Display();
        move (e_currLine, --e_currIndex);
      }
      default: {                                             // if letter TODO: specify if alpha char
        e_man->InsertChar(e_currLine, e_currIndex, e_key);   // insert char at current cursor line and index
        clear();                                             // clear previous contents TODO: IS THIS EFFICIENT?
        this->Display();                                     // update state of ncurses windows
        move (e_currLine, ++e_currIndex);                    // move cursor to next index
        break;
      }
    }
  } // HANDLEINPUT ()

  // Delete current index of current liner TODO
  void Editor::Delete(int ln, int in) {
    e_man->DeleteChar(e_currLine, in);
  } // DELETE (INT, INT)

  // return state of Editor (should or shouldn't close)
  bool Editor::ShouldClose() {
    if (e_shouldClose) {                                     // return true if state is should close
      return 1;
    }
    else {                                                   // else return 0 (shouldn't close)
      return 0;
    }
  } // SHOULDCLOSE ()
} // END NAMESPACE COMET