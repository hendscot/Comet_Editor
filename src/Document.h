#ifndef DOCUMENT_H
#define DOCUMENT_H
class FileHandler;
class Document {
public:
  Document  ();
  ~Document ();
  void LoadDocument(const char*);
  char* buffer;

  unsigned GetSize();

private:
  FileHandler* FH;
  unsigned bufSize;
};





#endif // DOCUMENT_H
