#ifndef LINE_H
#define LINE_H
const int STR_SIZE = 80;                                   // line length is defined with a max of 80 chars
// BEGIN COMET NAMESPACE
namespace Comet {
    Class String;
    namespace Core {
     // BEGIN LINE CLASS
        class Line {
        friend class LineManager;                                  // Share with Line manager
        // BEGIN PUBLIC DATA
        public:
            Line                           ();                 // No parameter constructor
            Line                           (const Line&);      // Copy constructor to create duplicate liner
            ~Line                          ();                 // Destructor
            int End                        ();
            int
            Length                         ();                 // Return string length
        // END PUBLIC DATA

        Line*                          next;               // pointer to address of next line
        Line*                          prev;               // pointer to address of previous line
        Comet::String*                 str;                // line data is maintained as type Comet::String
        // BEGIN PRIVATE DATA
        private:
            bool                           newL;               // stores state of line (contains a newline or not)
            unsigned                       currIn;             // maintains current index of line
            int                            size;               // stores line length
            static unsigned                lineAmnt;           // maintains total number of lines existing in the application
        // END PRIVATE DATA
        }; // LINE CLASS
    }
} // COMET NAMESPACE
#endif // LINE_H
