#include "../../includes/Interface/GhostEditor.h"
// BEGIN NAMESPACE Ghost
namespace Ghost {
  namespace Interface {
    GhostEditor* GhostEditor::ghostEditor_ = NULL;

    GhostEditor* Editor::GetGhostInstance () {
      return (!ghostEditor_) 
             ? ghostEditor_ = new Editor ()
             : ghostEditor_;
    }

    void GhostEditor::DeleteGhostInstance () {
      delete ghostEditor_;
      ghostEditor_ = NULL;
    }

    // Constructing a new Editor
    GhostEditor::GhostEditor() {
    } // EDITOR (CHAR*)

    // Deconstruct Editor
    GhostEditor::~GhostEditor() {
      DeleteGhostInstance ();
    } // ~EDITOR ()

    // Editor main system loop
    bool GhostEditor::Run() {
      while (!ShouldClose()) {                            // run actions while state is good
        Update();                                         // run update method to get input etc...
      }
      DeleteGhostInstance ();
      return 1; // fix later
    } // RUN ()

    // methods to be run within main system loop
    void GhostEditor::Update() {
      Poll ();                                                  // call method to acquire and handle user input
    } // UPDATE ()

    // return state of Editor (should or shouldn't close)
    bool GhostEditor::ShouldClose() {
      if (shouldClose_) {                                     // return true if state is should close
        return 1;
      }
      else {                                                   // else return 0 (shouldn't close)
        return 0;
      }
    } // SHOULDCLOSE ()
  }
} // END NAMESPACE Ghost
