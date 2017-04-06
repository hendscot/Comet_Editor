#ifndef GHOST_EDITOR_CORE_H
#define GHOST_EDITOR_CORE_H
namespace Ghost {
    namespace Core {
        class LineManager;
        class GhostEditorCore {
            // BEGIN PROTECTED
            protected:
                // SPECIALS
                GhostEditorCore  ();
                ~GhostEditorCore ();
                // PUBLIC METHODS
                void         Load              (const char*);
                void         Save              ();
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
                #define      ENTER           0x0A
                #define      TAB             0x09
                const int    LINE_OFFSET   = 0x02;
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
