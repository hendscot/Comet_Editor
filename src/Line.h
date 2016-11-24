#ifndef LINE_H
#define LINE_H
const int CHMAX = 80;
class Line {
friend class LineMan;
public:
    Line();
    Line(const Line&);
    ~Line();

private:
    Line* next;
    Line* prev;
    char  chr[CHMAX];
    unsigned lineNO;
    unsigned currIn;
    unsigned size;
    static unsigned lineAmnt;
  };
  typedef Line* LPTR;
#endif // LINE_H
