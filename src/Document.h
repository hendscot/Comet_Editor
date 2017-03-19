#ifndef DOCUMENT_H
#define DOCUMENT_H
class FileHandler;
#include "../utils/Comet-String/String.h"
class Document {
public:
  Document                                         ();
  ~Document                                        ();
  bool LoadDocument                                (const char*);
  bool SaveDocument                                ();
  Comet::String*                                   buffer;

  // PUBLIC ACCESSORS
  unsigned                                         GetSize();

private:
  FileHandler*                                     FH;
  const char*                                      doc_path;
  unsigned                                         bufSize;
  int                                              status;
};
#endif // DOCUMENT_H
