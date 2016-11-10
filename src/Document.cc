#include "../utils/FileHandler.h"
#include "Document.h"

Document::Document() {
  FH = new FileHandler;
}

Document::~Document() {

}

void Document::LoadDocument(const char* path) {
  buffer = FH->Read(path);
}
