#ifndef EDITOR_H
#define EDITOR_H
class Document;
class LineMan;
class Editor {
public:
  
   Editor                        (char*);
  ~Editor                        ();



  void         Display           ();
  void         LoadFile          ();
  void         SaveFile          ();
  void         Update            ();
  void         Delete            (int, int);

  bool         ShouldClose       ();
private:
  
  char*        e_path;
  bool         e_shouldClose;
  int          e_key;
  int          e_col;
  int          e_row;
  LineMan*     e_man;
  Document*    e_doc;
  unsigned     e_currLine;

};
#endif // EDITOR_H
