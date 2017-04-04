#include <fstream>
#include "Document.h"
namespace Comet {
  namespace IO {
    Document::d_stat = 0;
    Document::d_buf  = NULL;

    Document::Document() {
    }

    Document::~Document() {
    }

    bool Document::LoadDocument(const char* path) {
      std::ifstream fin(path);
      fin.seekg(0, std::ios::end);
      int docLen = fin.tellg();
      fin.seekg(0, std::ios::beg);
      char* buffer = new char [docLen];
      fin.read(buffer, docLen);
      fin.close();
      d_buf  = new Comet::String(buffer);
      delete buffer;
      d_len  = buffer->Length();
      return 1; // return status later
    }

    bool Document::SaveDocument(const char* path, Comet::Line* ln) {
      std::ofstream fout(path);
      Comet::Line* temp = ln;
      do {
        fout.write(temp->str->GetBuff(), temp->str->Length());
        fout.write("\n", 2);
        temp = temp->next;
      } while (temp != ln);
      fout.close();
      return 1;
    }

    unsigned Document::GetSize(){
      return d_buf->Length();
    }

    const char* Document::GetBuffer() {
      return d_buf;
    }

    void Document::CleanUp() {
      delete d_buf;
      d_buf  = NULL;
    }
  }
}