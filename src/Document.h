#ifndef DOCUMENT_H
#define DOCUMENT_H
class FileHandler;
class Document {
public:
  Document  ();
  ~Document ();
  void LoadDocument(const char*);
  char* buffer;

private:
  FileHandler* FH;

};





#endif // DOCUMENT_H
