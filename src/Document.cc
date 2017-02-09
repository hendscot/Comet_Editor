#include "../utils/FileHandler.h"
#include "Document.h"
#include <iostream>

Document::Document() {
  FH = new FileHandler;
}

Document::~Document() {

}

bool Document::LoadDocument(const char* path) {
  buffer = FH->Read(path);
  bufSize = FH->GetLength();
  return 1; // return status later
}


unsigned Document::GetSize(){
  return bufSize;
}
