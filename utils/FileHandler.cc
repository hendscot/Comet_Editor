#include "FileHandler.h"
#include <iostream>

FileHandler::FileHandler() {
  FH_doc = NULL;
  FH_docLen = 0;
}

FileHandler::~FileHandler() {
}

char* FileHandler::Read (const char* path) {
  FH_doc = fopen (path, "rt");
  if (FH_doc == NULL) perror("ERROR"); // TODO handle if file not opened
  fseek (FH_doc, 0, SEEK_END);
  FH_docLen = ftell (FH_doc);
  rewind (FH_doc);
  buffer = new char [sizeof(char) * FH_docLen];
  if (!buffer) ; // TODO: handle if memory not alloc
  fread (buffer, 1, FH_docLen, FH_doc); // TODO store return code in var
  fclose(FH_doc);
  return buffer;
}

unsigned FileHandler::GetLength(){
  return this->FH_docLen;
}
