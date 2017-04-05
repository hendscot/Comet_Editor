#include <fstream>
#include "../../includes/Core/Line.h"
#include "../../includes/IO/Document.h"
namespace Ghost {
  namespace IO {
    int Document::d_stat = 0;
    Comet::String* Document::d_buf  = NULL;

    Document::Document() {
    }

    Document::~Document() {
    }

    bool Document::LoadDocument(const char* path) {
      std::ifstream fin(path, std::ifstream::binary);
      fin.seekg(0, std::ios::end);
      int docLen = fin.tellg();
      fin.seekg(0, std::ios::beg);
      char* buffer = new char [docLen + 1];
      buffer[docLen] = '\0';
      fin.read(buffer, docLen);
      fin.close();
      d_buf  = new Comet::String(buffer);
      delete buffer;
      return 1; // return status later
    }

    bool Document::SaveDocument(const char* path, Ghost::Core::Line* ln) {
      std::ofstream fout(path);
      Ghost::Core::Line* temp = ln;
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
      return d_buf->GetBuff();
    }

    void Document::CleanUp() {
      delete d_buf;
      d_buf  = NULL;
    }
  }
}
