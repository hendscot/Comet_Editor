#include "FileHandler.h"
#include <fstream>

unsigned FileHandler::docLen = 0;
char*    FileHandler::buffer = NULL;

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

void FileHandler::Write (const char* path, Comet::Line* ln) {
  std::ofstream fout(path);
  Comet::Line* temp = ln;
  do {
    fout.write(temp->str->GetBuff(), temp->str->Length());
    fout.write("\n", 2);
    temp = temp->next;
  } while (temp != ln);
  fout.close();
}

unsigned FileHandler::GetLength(){
}
