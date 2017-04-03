#define _CRT_SECURE_NO_WARNINGS
#ifndef FILEHANDLER_H
#define FILEHANDLER_H
class LineManager;
class FileHandler {
public:
  ~FileHandler ();
  static char*    Read   (const char*);
  static void     Write  (const char*, const LineManager&*);
  static unsigned GetLength();
private:
  FileHandler  ();
  unsigned docLen;
  char*    buffer;
};

#endif //FILEHANDLER_H
