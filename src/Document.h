#ifndef DOCUMENT_H
#define DOCUMENT_H
class FileHandler;
class LineManager;
class Document {
public:
  Document                                         ();
  ~Document                                        ();
  bool LoadDocument                                (const char*);
  bool SaveDocumentAs                              (const char*);
  bool SaveDocument                                (char*);
  char*                                            buffer;

  // PUBLIC ACCESSORS
  unsigned                                         GetSize();

private:
  FileHandler*                                     FH;
  LineManager*                                     LM;
  const char*                                      doc_path;
  unsigned                                         bufSize;
  int                                              status;
};
#endif // DOCUMENT_H