#ifndef LINEMAN_H
#define LINEMAN_H
// BEGIN COMET NAMESPACE
namespace Comet {
    class Line;                                                      // Forward declare line class
    // BEGIN LINEMAN CLASS
    class LineMan {
    typedef Line* LPTR;                                              // line pointer typedef
    // BEGIN PUBLIC DATA
    public:
        LineMan();                                                   // no param constructor
        ~LineMan();                                                  // destructor
        void Append(char);                                           // Append char to latest index
        void Display();                                              // SHOULD PROBABLY REMOVE THIS 
        void DeleteChar(int, int);                                   // Delete char from target at line at target index
        void InsertChar(int, int, char);                             // Insert char to target line at target index
        void InsertLine();                                           // insert a new line
        void DeleteLine(LPTR);                                       // delete a given line
    // END PUBLIC DATA

    // BEGIN PRIVATE DATA
    private:
        LPTR l_strt;                                                 // Maintain first line
        LPTR l_end;                                                  // Maintaine last line
        void Newline();                                              // create a new line at end of line list
        bool NoLines();                                              // check if any lines exist
        bool Full(LPTR);                                             // check if line is at max defined capacity
    // END PRIVATE DATA
    }; // END LINEMAN CLASS
} // END COMET NAMESPACE
#endif //LINEMAN_H