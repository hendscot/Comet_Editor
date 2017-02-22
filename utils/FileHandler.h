#define _CRT_SECURE_NO_WARNINGS
#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stdio.h>
#include <stdlib.h>


class FileHandler {
public:
  FileHandler  ();
  ~FileHandler ();
  char* Read   (const char*);
  void  Write  (const char*, char*);

  unsigned GetLength();

private:
  FILE* FH_doc;
  unsigned FH_docLen;
  char* buffer;
};

#endif //FILEHANDLER_H