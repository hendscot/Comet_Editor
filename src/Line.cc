#include "Line.h"
#include <cstdlib>
// init static lineAmnt var
unsigned Line::lineAmnt = 0;

// No param constructor
Line::Line() {
    next = NULL;
    prev = NULL;
    ++lineAmnt;
    lineNO = lineAmnt;
    currIn = 0;
    size = 0;
    for (int i = 0; i < CHMAX; i++) {
        chr[i] = '\0';
    }
}

Line::Line(const Line& rl){
    next = NULL;
    prev = NULL;
    ++lineAmnt;
    lineNO = lineAmnt;
    currIn = 0;
    for (int i = 0; i < CHMAX || rl.chr[i]; i++) {
        chr[i] = rl.chr[i];
    }
}

// Destructor
Line::~Line() {

}



