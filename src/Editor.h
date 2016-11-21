#ifndef EDITOR_H
#define EDITOR_H
class Document;
class LineMan;
class Editor {
public:
  Editor  ();
  ~Editor ();
  void Display();
  void LoadFile();
  void SaveFile();
private:
  char* e_path;
  LineMan* e_man;
  Document* e_doc;

};
#endif // EDITOR_H
