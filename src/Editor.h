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
  void Delete(unsigned);
private:
  char* e_path;
  LineMan* e_man;
  Document* e_doc;
  unsigned currLine;

};
#endif // EDITOR_H
