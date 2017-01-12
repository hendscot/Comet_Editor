#ifndef LINEMAN_H
#define LINEMAN_H
// BEGIN COMET NAMESPACE
namespace Comet {
    class Line;                                                      // 
    class LineMan {
    typedef Line* LPTR;
    public:
        LineMan();
        ~LineMan();
        void Append(char);
        void Display();
        void DeleteChar(int, int);
        void InsertChar(int, int, char);
        void InsertLine();
        void DeleteLine(LPTR);
    private:
        LPTR l_strt;
        LPTR l_end;
        void Newline();
        bool NoLines();
        bool Full(LPTR);
    };
}
#endif //LINEMAN_H
