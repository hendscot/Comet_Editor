#ifndef LINE_H
#define LINE_H
#include "String.h"
const int STR_SIZE = 80;
class Line {
friend class LineMan;
public:
    Line();
    Line(const Line&);
    ~Line();

private:
    Line*           next;
    Line*           prev;
    Comet::String*  str;
	bool            newL;
    unsigned        lineNO;
    unsigned        currIn;
    unsigned        size;
    static unsigned lineAmnt;
  };
  typedef Line* LPTR;
#endif // LINE_H
