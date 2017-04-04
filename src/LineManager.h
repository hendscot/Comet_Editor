#ifndef LineManager_H
#define LineManager_H
// BEGIN COMET NAMESPACE
class String;
namespace Comet {
    class Line;                                                      // Forward declare line class
    // BEGIN LineManager CLASS
    class LineManager {
    typedef Line* LPTR;                                              // line pointer typedef
    // BEGIN PUBLIC DATA
    public:
        LineManager();                                               // no param constructor
        ~LineManager();                                              // destructor
        void Append(char);                                           // Append char to latest index
        void Append(char, const int);
        void DeleteChar(const int, const int);                                   // Delete char from target at line at target index
        void InsertChar(const int, const int, char);                             // Insert char to target line at target index
        void InsertBreak(const int, const int);
        int  GetLength (const int) const;
        int  GetLineCount () const;
        Line* GetStart() const;
        void Display() const;
        Line* First        ();
    // END PUBLIC DATA

    // BEGIN PRIVATE DATA
    private:
        LPTR    l_strt;                                                 // Maintain first line
        LPTR    l_end;
        mutable                                                  // Maintain last line
        LPTR    l_iter;                                                 // Used for iterating through list
        void    Newline();                                              // create a new line at end of line list
        void    InsertLineAfter(LPTR);                                  // insert a new line
        void    InsertLineBefore(LPTR);
        void    DeleteLine(LPTR);                                       // delete a given line
        bool    NoLines();                                              // check if any lines exist
        bool    Full(LPTR);                                             // check if line is at max defined capacity
        void    SelfDestruct ();
        int  ConcatLines  (LPTR);
    // END PRIVATE DATA
    }; // END LineManager CLASS
} // END COMET NAMESPACE
#endif //LineManager_H
