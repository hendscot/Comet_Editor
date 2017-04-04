#define _CRT_SECURE_NO_WARNINGS
#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "../src/Line.h"
class FileHandler {
public:
  ~FileHandler ();
  static char*    Read   (const char*);
  static void     Write  (const char*, Comet::Line*);
  static unsigned GetLength();
private:
  FileHandler  ();
  static unsigned docLen;
  static char*    buffer;
};

#endif //FILEHANDLER_H
