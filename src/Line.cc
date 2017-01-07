#include "Line.h"
#include "String.h"
#include <cstdlib>
// init static lineAmnt var
unsigned Line::lineAmnt = 0;

// No param constructor
Line::Line() {
    next = NULL;
    prev = NULL;
	newL = false;
    ++lineAmnt;
    lineNO = lineAmnt;
    currIn = 0;
    size = 0;
	str = new Comet::String(STR_SIZE);
}

Line::Line(const Line& rl){
    next = NULL;
    prev = NULL;
    ++lineAmnt;
    lineNO = lineAmnt;
    currIn = 0;
    
}

// Destructor
Line::~Line() {

}



