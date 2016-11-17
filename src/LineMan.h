#ifndef LINEMAN_H
#define LINEMAN_H
class Line;
class LineMan {
  typedef Line* LPTR;
public:
     LineMan();
    ~LineMan();
    void Append(char);
    void Display();
    void Delete(int, int);
private:
    LPTR l_strt;
    LPTR l_end;
    void Newline();
    bool NoLines();
    bool Full(LPTR);
};
#endif //LINEMAN_H
