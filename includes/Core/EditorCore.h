#ifndef EDITOR_CORE_H
#define EDITOR_CORE_H
namespace Comet {
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
                bool         shouldClose; 
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
                const int    ENTER         = 0x0A;
                const int    TAB           = 0x09;
                const int    SPACE         = 0x20;
                const int    TAB_SIZE      = 0x04;
                const int    UP            = KEY_UP;
                const int    DOWN          = KEY_DOWN;
                const int    LEFT          = KEY_LEFT;
                const int    RIGHT         = KEY_RIGHT;
                const int    SAVE          = KEY_SLEFT;
                const int    BACKSPACE     = KEY_BACKSPACE;
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
