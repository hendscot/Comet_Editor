#include "FileHandler.h"
#include <fstream>



FileHandler::FileHandler() {
  FH_doc = NULL;
  FH_docLen = 0;
}

FileHandler::~FileHandler() {
  delete buffer;
}

char* FileHandler::Read (const char* path) {
  /*FH_doc = fopen (path, "rb");
  if (FH_doc == NULL) perror("ERROR"); // TODO handle if file not opened
  fseek (FH_doc, 0, SEEK_END);
  FH_docLen = ftell (FH_doc);
  rewind (FH_doc);
  buffer = new char [sizeof(char) * FH_docLen + 1];
  if (!buffer) ; // TODO: handle if memory not alloc
  fread (buffer, 1, FH_docLen, FH_doc); // TODO store return code in var
  fclose(FH_doc);
  return buffer;*/

  std::ifstream fin(path);
  fin.seekg(0, std::ios::end);
  FH_docLen = fin.tellg();
  fin.seekg(0, std::ios::beg);
  buffer = new char [FH_docLen];
  fin.read(buffer, FH_docLen);
  fin.close();
  return buffer;
}

// WORKING BUT THIS IS PLACEHOLDER CODE (NEED SOME WAY TO PRINT LINES FROM DOC)
void FileHandler::Write (const char* path, char* buff) {
  std::ofstream fout(path);
  fout.write(buff, sizeof(buff));
  fout.close();
}

unsigned FileHandler::GetLength(){
  return this->FH_docLen;
}
