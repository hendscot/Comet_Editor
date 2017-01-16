#include "Editor.h"
#include "EditorCore.h"
// BEGIN NAMESPACE COMET
namespace Comet {
  // Constructing a new Editor
  Editor::Editor() {
    Init ();
  } // EDITOR (CHAR*)

  // Deconstruct Editor
  Editor::~Editor() {

  } // ~EDITOR ()

  // Editor main system loop
  void Editor::Run() {
    while (!ShouldClose()) {                            // run actions while state is good
      Update();                                         // run update method to get input etc...
    }
  } // RUN ()

  // methods to be run within main system loop
  void Editor::Update() {
    Poll ();                                                  // call method to acquire and handle user input
  } // UPDATE ()

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