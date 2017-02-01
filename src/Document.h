#ifndef DOCUMENT_H
#define DOCUMENT_H
class FileHandler;
class Document {
public:
  Document                                         ();
  ~Document                                        ();
  bool LoadDocument                                (const char*);
  bool SaveDocumentAs                              (const char*);
  bool SaveDocument                                ();
  char*                                            buffer;

  // PUBLIC ACCESSORS
  unsigned                                         GetSize();

private:
  FileHandler*                                     FH;
  unsigned                                         bufSize;
  int                                              status;
};
#endif // DOCUMENT_H