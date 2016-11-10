#include <iostream>
#include "Document.h"

int main (int argc, char* argv[]) {
  Document* doc = new Document;
  doc->LoadDocument("~/Documents/Editor/test/docs/helloworld.cc");

  return 1;
}
