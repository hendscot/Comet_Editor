#ifndef DOCUMENT_H
#define DOCUMENT_H
class LineManager;
class Document {
public:
  Document                                         ();
  ~Document                                        ();
  bool LoadDocument                                (const char*);
  bool SaveDocument                                (const LineManager&);
  Comet::String*                                   buffer;

  // PUBLIC ACCESSORS
  unsigned                                         GetSize();

private:
  const char*                                      doc_path;
  unsigned                                         bufSize;
  int                                              status;
};
#endif // DOCUMENT_H
