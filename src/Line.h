#ifndef LINE_H
#define LINE_H
#include "../utils/String.h"
const int STR_SIZE = 80;                                   // line length is defined with a max of 80 chars
// BEGIN COMET NAMESPACE
namespace Comet {
    // BEGIN LINE CLASS
    class Line {
    friend class LineMan;                                  // Share with Line manager
    // BEGIN PUBLIC DATA
    public:
        Line                           ();                 // No parameter constructor
        Line                           (const Line&);      // Copy constructor to create duplicate liner
        ~Line                          ();                 // Destructor
    // END PUBLIC DATA

    // BEGIN PRIVATE DATA
    private:
        Line*                          next;               // pointer to address of next line
        Line*                          prev;               // pointer to address of previous line
        Comet::String*                 str;                // line data is maintained as type Comet::String
        bool                           newL;               // stores state of line (contains a newline or not)
        unsigned                       lineNO;             // maintains corresponding line number
        unsigned                       currIn;             // maintains current index of line
        unsigned                       size;               // stores line length
        static unsigned                lineAmnt;           // maintains total number of lines existing in the application
    // END PRIVATE DATA
    }; // LINE CLASS                      
} // COMET NAMESPACE
#endif // LINE_H
