#ifndef STRING_H
#define STRING_H

#include <iostream>

//#define NULL ( (void *) 0)
#define COMET_STRING_VERSION     0.1.0
#define CASEDIFF                 32
#define CAP_BEG                  65
#define CAP_END                  90
#define LOW_BEG                  97
#define LOW_END                  122
#define OFLW_SIZE                1

namespace Comet {
    class String {
        public:
            // constructors
            String                (int size = 0);
            String                (const char*);
            
            // copy constructor
            String                (const String&);
            
            // destructor
            ~String               ();
            
            // operator overloads
            String& operator  =   (const String&);
            String& operator  =   (const char*);
            String  operator  +   (const char*);
            String  operator  +=  (const String&);
            String  operator  +=  (const char*);
            String  operator  +   (const String&);            
            bool    operator  ==  (const String&)  const;
            bool    operator  ==  (const char*)    const;
            bool    operator  !=  (const String&)  const;
            bool    operator  !=  (const char*)    const;
            bool    operator  >   (const char*)    const;
            bool    operator  >   (const String&)  const;
            bool    operator  <   (const char*)    const;
            bool    operator  <   (const String&)  const;
            bool    operator  >=  (const char*)    const;
            bool    operator  >=  (const String&)  const;
            bool    operator  <=  (const char*)    const;
            bool    operator  <=  (const String&)  const;
            char&   operator  []  (const int)      const;

            // Public Accessors
            int     Length    ()                   const;
            char    Overflow  ()                   const;
            char*   GetBuff   ()                   const;

            // Public Mutators
            void    Replace       (int, char);
            void    Replace       (int, int, const char*);
            void    Append        (char);
            bool    Insert        (int, char);
            void    Delete        (int);
            void    Reverse       ();
            bool    Upper         ();
            bool    Upper         (int);
            bool    Upper         (int, int);
            bool    Lower         ();
            bool    Lower         (int);
            bool    Lower         (int, int);
            void    Concat        (const String&);
            String Substr        (int, int);

        private:
            // Private Data Members
            mutable 
            int     iter;
            char    overflow[OFLW_SIZE];
            char*   s_buf;
            int     s_bLen;
            int     s_sLen;

            // Private Mutators
            void    Alloc         (int);
            void    Dealloc       ();
            void    Term          ();
            void    Fill          (const char*);
            void    Concat        (const char*, const char*);

            // Private helper functions
            int  len              (const char*)    const;
            bool isAlpha          (const char)     const;
            bool isUpper          (const char)     const;
            bool isLower          (const char)     const;

            // friends
            friend std::ostream& operator<<(std::ostream&, const String&);
    };
}

#endif // STRING_H