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
        bool         SaveDocument    (const char*, Comet::Core::Line*);
        // PUBLIC ACCESSORS
        static
        unsigned       GetSize       ();
        static
        const char*    GetBuffer     ();
        static
        void           CleanUp       ();
      private:
        Document                     ();
        static int            d_stat;
        static Comet::String* d_buf;
    };
  }
}
#endif // DOCUMENT_H
