#include "Line.h"
#include <cstdlib>
// BEGIN NAMESPACE COMET
namespace Comet {
    // init static lineAmnt var
    unsigned Line::lineAmnt = 0;                               // maintains number of existing line nodes

    // TODO add insert etc... methods to prevent direct string access 

    // No param constructor
    Line::Line() {
        next = NULL;                                           // set pointer to next line node to NULL
        prev = NULL;                                           // set pointer to previous line node to NULL
        newL = false;                                          // set state of line to false
        ++lineAmnt;                                            // creating a line node so increase line node total
        lineNO = (lineAmnt - 1);                               // current line number is equal to total lines - 1
        currIn = 0;                                            // line is new so latest index is 0
        size = 0;                                              // line is new so size is 0;
        str = new Comet::String(STR_SIZE);                     // allocate new string with space of str max length
    } // Line ()

    // TODO: FINISH
    Line::Line (const Line& rl){
        next = NULL;
        prev = NULL;
        ++lineAmnt;
        lineNO = lineAmnt;
        currIn = 0;
    } // Line (const Line&)

    // Destructor
    Line::~Line () {
        --lineAmnt;                                            // removing line so decrease line amount
        delete str;                                            // destroy string data
    } // Line ()    
    
    int Line::Length () {
        return str->Length();
    }

    int Line::End () {
        return (Length() - 1);
    }

    bool Line::IsOF () {
        return str->Overflowed();
    }

    char Line::PopOF () {
        return str->GetOverflow();
    }
} // END NAMESPACE COMET
