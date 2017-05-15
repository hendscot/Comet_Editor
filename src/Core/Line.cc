#include <cstdlib>
#include "../../includes/Core/Line.h"
// BEGIN NAMESPACE Ghost
using namespace Ghost;
using namespace Core;
// init static lineAmnt var
unsigned Line::lineAmnt = 0;                               // maintains number of existing line nodes

// TODO add insert etc... methods to prevent direct string access

// No param constructor
Line::Line() {
    next = NULL;                                           // set pointer to next line node to NULL
    prev = NULL;                                           // set pointer to previous line node to NULL
    newL = false;                                          // set state of line to false
    ++lineAmnt;                                            // creating a line node so increase line node total
    currIn = 0;                                            // line is new so latest index is 0
    size = 0;                                              // line is new so size is 0;
    str = new Comet::String(STR_SIZE);                     // allocate new string with space of str max length
}

Line::Line (const Line& rl){
    this->next = rl.next;
    this->prev = rl.prev;
    this->str(rl.str);
    ++lineAmnt;
}

// Destructor
Line::~Line () {
    --lineAmnt;                                            // removing line so decrease line amount
    delete str;                                            // destroy string data
}

int
Line::Length () {
    return str->Length();
}

int
Line::End () {
    return (Length() - 1);
}
