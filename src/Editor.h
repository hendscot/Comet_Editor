#ifndef EDITOR_H
#define EDITOR_H
class Document;
class LineMan;
namespace Comet {
  class Editor {
  // BEGIN PUBLIC DATA
  public:
    // CONSTRUCTOR/DESTRUCTOR
    Editor                         (char*);     // Simple constructor   - constructs new Editor object with pathname of file
    ~Editor                        ();          // Simple deconstructor - destroys LineMan and Document objects

    // PUBLIC METHODS
    Run                            ();          // Initiates Editor objects system loop

  // END PUBLIC DATA

  // BEGIN PRIVATE DATA
  private:
    // PRIVATE MEMBERS
    char*        e_path;                        // Maintains string of filepath
    bool         e_shouldClose;                 // State variable that alerts system loop to end
    int          e_key;                         // Stores value of key pressed by user
    int          e_currLine;                    // Current column (index) to be passed to ncurses and to manipulate files
    int          e_currIndex;                   // Current row (line) to be passed to ncurses and to manipulate files
    LineMan*     e_man;                         // LineMan object which contains and controls lines
    Document*    e_doc;                         // Document object for loading and saving files to be manipulated

    // PRIVATE METHODS
    void         Display           ();          // Call LineMan class Display method, loads state of file into ncurses window after change
    void         Init              ();          // Initialize ncurses and private members
    void         LoadFile          ();          // Call Document class LoadDocument method which loads file state into a doc buffer
    void         SaveFile          ();          // Save current file state
    void         Update            ();          // Method used in main loop, runs necessary system methods (HandleInput)
    void         Delete            (int, int);  // Interface for LineMan Deletechar method (deletes specified index at current line)

    bool         ShouldClose       ();          // Returns state of e_shouldClose boolean member (instructs system loop to end)

  // END PRIVATE DATA
  };
}
#endif // EDITOR_H
