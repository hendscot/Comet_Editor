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
      std::filebuf*  fbuf = fin.rdbuf();
      std::size_t fsize = fbuf->pubseekoff (0, fin.end, fin.in);
      fbuf->pubseekpos(0, fin.in);
      char* buf = new char [fsize + 1];
      buf[fsize] = '\0';
      fbuf->sgetn (buf, fsize);
      fin.close();
      d_buf = new Comet::String(buf);
      delete [] buf;
      return 1; // return status later
    }

    bool Document::SaveDocument(const char* path, Ghost::Core::Line* ln) {
      std::ofstream fout(path);
      Ghost::Core::Line* temp = ln;
      do {
        fout.write(temp->str->GetBuff(), temp->str->Length());
        fout.write("\n", 1);
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
