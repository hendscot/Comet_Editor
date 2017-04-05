#ifndef LineManager_H
#define LineManager_H
// BEGIN COMET NAMESPACE
class String;
namespace Comet {
    namespace Core {
        class Line;
        // BEGIN LineManager CLASS
        class LineManager {
        typedef Line* LPTR; 
        // BEGIN PUBLIC DATA
        public:
            LineManager();
            ~LineManager();

            // PUBLIC METHODS
            void Append(char);
            void Append(char, const int);
            void DeleteChar(const int, const int);
            void InsertChar(const int, const int, char);
            void InsertBreak(const int, const int);
            int  GetLength (const int) const;
            int  GetLineCount () const;
            Line* GetStart() const;
            void Display() const;
            Line* First        ();
        // END PUBLIC DATA

        // BEGIN PRIVATE DATA
        private:
            // PRIVATE MEMBERS
            LPTR    strt_;
            LPTR    end_;
            mutable
            LPTR    iter_;

            //PRIVATE METHODS
            void    Newline();
            void    InsertLineAfter(LPTR);
            void    InsertLineBefore(LPTR);
            void    DeleteLine(LPTR);
            bool    NoLines();
            bool    Full(LPTR);
            void    SelfDestruct ();
            int  ConcatLines  (LPTR);
        // END PRIVATE DATA
        }; // END LineManager CLASS
    }
} // END COMET NAMESPACE
#endif //LineManager_H
