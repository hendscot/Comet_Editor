#ifndef EDITOR_CORE_H
#define EDITOR_CORE_H
#include <ncurses.h>
namespace Ghost {
    namespace Core {
        class LineManager;
        class EditorCore {
            public:
                // SPECIALS
                EditorCore  ();
                ~EditorCore ();
                // PUBLIC METHODS
                void         Load              (const char*);
                void         Save              ();
            // BEGIN PROTECTED
            protected:
                // PROTECTED MEMBERS
                bool         shouldClose_;
                // PROTECTED METHODS
                void         InitGuiOptions    ();
                void         Poll              ();
            // BEGIN PRIVATE DATA
            private:
                // PRIVATE MEMBERS
                const char*  path_;
                int          key_;
                int          currLine_;
                int          currIndex_;
                LineManager* lines_;
                // PRIVATE CONSTANTS
                const int    LINE_OFFSET   = 0x02;
                #define    ENTER          0x0A
                #define   TAB           0x09
                const int    SPACE         = 0x20;
                const int    TAB_SIZE      = 0x04;
                // PRIVATE METHODS
                void         DisplayToTerminal ();
                void         HandleKeyInput    ();
                void         MoveCursorUp      ();
                void         MoveCursorDown    ();
                void         MoveCursorLeft    ();
                void         MoveCursorRight   ();
                void         RemoveCharacter   ();
                void         InsertCharacter   ();
                void         InsertNewline     ();
                void         InsertTab         ();
                void         Insert            (int, int, char);
                void         Delete            (int, int);
        };
    }
}
#endif // EDITOR_CORE_H
