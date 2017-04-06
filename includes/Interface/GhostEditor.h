#ifndef GHOST_EDITOR_H
#define GHOST_EDITOR_H
#include "../../includes/Core/GhostEditorCore.h"
namespace Ghost {
  namespace Interface {
    class GhostEditor : protected 
    Ghost::Core::GhostEditorCore {
    // BEGIN PUBLIC DATA
      public:
        // PUBLIC METHODS
        bool              Run               ();
        GhostEditor*      GetGhostInstance  ();
      // END PUBLIC DATA

      // BEGIN PRIVATE DATA
      private:
        // PRIVATE METHODS
        GhostEditor                         ();
        GhostEditor                         (const GhostEditor&);
        ~GhostEditor                        ();
        GhostEditor&      operator=         (const GhostEditor&);                        
        void              Update            ();
        bool              ShouldClose       ();
        static
        GhostEditor*      ghostEditor_;
      // END PRIVATE DATA
    };
  }
}
#endif // EDITOR_H
