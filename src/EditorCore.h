#ifndef EDITORCORE_H
#define EDITORCORE_H
#include "LineManager.h"
namespace Comet {
    namespace Core {
        #define  E_BEG      0x02
        #define  E_ENTER    0x0A
        #define  E_TAB      0x09
        #define  E_SPACE    0x20
        #define  E_TAB_SIZE 0x04
        class EditorCore {
        public:
            EditorCore  ();
            ~EditorCore ();

            void         Load              (const char*);  // Call Document class LoadDocument method which loads file state into a doc buffer
        protected:
            bool         e_shouldClose;                    // State variable that alerts system loop to end
            void         InitGUIOptions    ();             // Initialize ncurses and private members
            void         Poll              ();
            void         Save              ();             // Save current file state

        // BEGIN PRIVATE DATA
        private:
            // PRIVATE MEMBERS
            const char*  e_path;                           // Maintains string of filepath
            int          e_key;                            // Stores value of key pressed by user
            int          e_currLine;                       // Current column (index) to be passed to ncurses and to manipulate files
            int          e_currIndex;                      // Current row (line) to be passed to ncurses and to manipulate files
            LineManager* e_man;                            // LineMan object which contains and controls lines

            // PRIVATE METHODS
            void         Display           ();             // Call LineMan class Display method, loads state of file into ncurses window after change
            void         HandleInput       ();
            void         Insert            (int, int, char);
            void         Delete            (int, int);     // Interface for LineMan Deletechar method (deletes specified index at current line)
        };
    }
}
#endif // EDITORCORE_H
