#include "../utils/FileHandler.h"
#include "Document.h"
#include <iostream>

Document::Document() {
  FH = new FileHandler;
}

Document::~Document() {

}

bool Document::LoadDocument(const char* path) {
  doc_path = path;
  buffer = new Comet::String(FH->Read(doc_path));
  bufSize = buffer->Length();
  return 1; // return status later
}

bool Document::SaveDocument() {
  FH->Write("test2.txt", buffer);
  return 1;
}


unsigned Document::GetSize(){
  return bufSize;
}
