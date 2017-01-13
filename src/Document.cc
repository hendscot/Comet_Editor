#include "../utils/FileHandler.h"
#include "Document.h"
#include <iostream>

Document::Document() {
  FH = new FileHandler;
}

Document::~Document() {

}

void Document::LoadDocument(const char* path) {
  buffer = FH->Read(path);
  bufSize = FH->GetLength();
}

unsigned Document::GetSize(){
  return bufSize;
}
