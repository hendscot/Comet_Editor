#include "FileHandler.h"
#include "../src/LineManager.h"
#include <fstream>

FileHandler::FileHandler() {
}

FileHandler::~FileHandler() {
  delete buffer;
}

char* FileHandler::Read (const char* path) {
  std::ifstream fin(path);
  fin.seekg(0, std::ios::end);
  docLen = fin.tellg();
  fin.seekg(0, std::ios::beg);
  buffer = new char [docLen];
  fin.read(buffer, docLen);
  fin.close();
  return buffer;
}

void FileHandler::Write (const char* path, const LineManager&* doc) {
  std::ofstream fout(path);
  int lines = doc->GetLineCount ();
  LPTR* temp = doc->l_strt;
  for (int i = 0; i < lines; i++, temp = temp->next) {
    fout.write(temp->str->GetBuff(), temp->str->Length());
  }
  fout.close();
}

unsigned FileHandler::GetLength(){
  return this->FH_docLen;
}
