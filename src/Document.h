#ifndef DOCUMENT_H
#define DOCUMENT_H
#include "Line.h"
namespace Comet {
  namespace IO {
    class Document {
      public:
        ~Document                    ();
        static
        bool         LoadDocument    (const char*);
        static
        bool         SaveDocument    (const char*, Comet::Line*);
        // PUBLIC ACCESSORS
        static
        unsigned       GetSize       ();
        static
        const char*    GetBuffer     ();
        static
        void           CleanUp       ();
      private:
        Document                     ();
        int            d_stat;
        Comet::String* d_buf;
    };
  }
}
#endif // DOCUMENT_H
