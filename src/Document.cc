#include "../utils/FileHandler.h"
#include "Document.h"
#include <iostream>

Document::Document() {
}

Document::~Document() {

}

bool Document::LoadDocument(const char* path) {
  doc_path = path;
  buffer = new Comet::String(FileHandler::Read(doc_path));
  bufSize = buffer->Length();
  return 1; // return status later
}

bool Document::SaveDocument(Comet::Line* doc) {
  FileHandler::Write("test2.txt", doc);
  return 1;
}

unsigned Document::GetSize(){
  return bufSize;
}
