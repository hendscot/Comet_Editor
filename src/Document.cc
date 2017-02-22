#include "../utils/FileHandler.h"
#include "Document.h"
#include <iostream>

Document::Document() {
  FH = new FileHandler;
  LM = new LineManager;
}

Document::~Document() {
  delete FH;
  delete LM;
  delete buffer;
}

bool Document::LoadDocument(const char* path) {
  doc_path = path;
  buffer = FH->Read(doc_path);
  bufSize = FH->GetLength();
  
  return 1; // return status later
}

bool Document::SaveDocument(char* linebuffer) {
  delete buffer;
  buffer = linebuffer;
  // FH->Write("test2.txt", buffer);
  return 1;
}

bool Document::InitDoc () {
  for (int i = 0; i < length; i++){              // transfer buffer contents into lines in the line manager object
    LM->Append(buffer[i]);
  }
}
unsigned Document::GetSize(){
  return bufSize;
}
