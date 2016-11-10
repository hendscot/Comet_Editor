#ifndef DOCUMENT_H
#define DOCUMENT_H
class FileHandler;
class Document {
public:
  Document  ();
  ~Document ();
  void LoadDocument(const char*);

private:
  char* buffer;
  FileHandler* FH;

};





#endif // DOCUMENT_H
