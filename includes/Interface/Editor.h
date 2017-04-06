#ifndef EDITOR_H
#define EDITOR_H
#include "../../includes/Core/EditorCore.h"
namespace Ghost {
  namespace Interface {
    class Editor : public Ghost::Core::EditorCore {
    // BEGIN PUBLIC DATA
      public:
        // CONSTRUCTOR/DESTRUCTOR
        Editor                         ();     // Simple constructor   - constructs new Editor object with pathname of file
        ~Editor                        ();          // Simple deconstructor - destroys LineMan and Document objects

        // PUBLIC METHODS
        void Run                       ();          // Initiates Editor objects system loop

      // END PUBLIC DATA

      // BEGIN PRIVATE DATA
      private:
        // PRIVATE METHODS
        void         Update            ();          // Method used in main loop, runs necessary system methods (HandleInput)
        bool         ShouldClose       ();          // Returns state of e_shouldClose boolean member (instructs system loop to end)
      // END PRIVATE DATA
    };
  }
}
#endif // EDITOR_H
