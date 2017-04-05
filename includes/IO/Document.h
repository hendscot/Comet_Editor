#ifndef DOCUMENT_H
#define DOCUMENT_H
namespace Comet {
  namespace Core { class Line; }
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
