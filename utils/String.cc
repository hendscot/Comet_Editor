#include <cassert>
#include "String.h"
namespace Comet {
    // Default Constructor
    String::String(int size) {
        // NULL the buffer
        s_buf = NULL;
        
        s_sLen = 0;
        // allocate space
        Alloc(size);
    } // String::String()

    // Construct with a c-string
    String::String(const char* str) 
        : String(len(str)) {
        s_sLen = s_bLen;
        // use assignment overload to create
        *this = str;
    } // String::String(const char*)

    // Copy Constructor
    String::String(const String& str) 
        : String(str.s_sLen) {
        s_sLen = s_bLen;
        // use assignment overload to create
        *this = str;
    } // String::String(const String&)

    // Deconstructor
    String::~String() {
        // delete the buffer on deconstruction
        delete [] s_buf;
    } // String::~String()

    //************* Overloaded Operators ************************

    // Assignment (Two Strings)
    String& String::operator=(const String& str) {
        // Check that we're not assigning same objs
        if (this != &str) {
            // Only resize if new length is >= to buffer length
            if (str.s_sLen > s_bLen) {
                // allocate with new string size
                Alloc (str.s_sLen);
                s_sLen = str.s_sLen;
            }
            else {
                // else just terminate end
                s_sLen = str.s_sLen;
                //Term(); //DOES THIS EVEN WORK??
            }
            // assign buffer to assignee buffer
            FillFrom(str.s_buf);
        }
        return *this;
    } // operator+(const String&)

    // Assignment overload (String and C-String)
    String& String::operator=(const char* str) {
        int length = len(str);
        // only reallocate if new string length is > buffer length
        if (length > s_bLen) {
            Alloc (length);
            s_sLen = length;
        }
        else {
            s_sLen = length;
            //Term();
        }
        FillFrom(str);
        return *this;
    }

    //***************COMPARATORS************************************************
    // Compare two String objects
    bool String::operator==(const String& str) const {
        bool isEqual = true;
        // if lengths are different, not equal
        if (this->s_sLen != str.s_sLen)
            return false;
        else {
            // compare each element of both strings
            for (iter = 0; iter < this->s_sLen && isEqual == true; iter++) {
                // if even one char is different, not qual
                if (this->s_buf[iter] != str.s_buf[iter])
                    isEqual = false;
            }
        }
        return isEqual;
    }

    // Compare string with c-string
    bool String::operator==(const char* str) const {
        bool isEqual = true;
        if (this->s_sLen != len(str))
            return false;
        else {
            for (iter = 0; iter < this->s_sLen && isEqual == true; iter++) {
                if (this->s_buf[iter] != str[iter])
                    isEqual = false;
            }
        }
        return isEqual;
    }

    // compare two strings
    bool String::operator!=(const String& str) const {
        return !((*this) == str);
    }

    // compare string with c-string
    bool String::operator!=(const char* str) const {
        return !((*this) == str);
    }

    // compare string with c-string
    bool String::operator>(const char* str) const {
        return (this->s_sLen > len(str)) ? true : false;
    }

    // compare two strings
    bool String::operator>(const String& str) const {
        return (this->s_sLen > str.s_sLen) ? true : false;
    }

    // compare string with c-string
    bool String::operator<(const char* str) const {
        return (this->s_sLen < len(str)) ? true : false;
    }

    // compare two strings
    bool String::operator<(const String& str) const {
        return (this->s_sLen < str.s_sLen) ? true : false;
    }

    // compare string with c-string
    bool String::operator>=(const char* str) const {
        return (this->s_sLen >= len(str)) ? true : false;
    }

    // compare two strings
    bool String::operator>=(const String& str) const {
        return (this->s_sLen >= str.s_sLen) ? true : false;
    }

    // compare string with c-string
    bool String::operator<=(const char* str) const {
        return (this->s_sLen <= len(str)) ? true : false;
    }

    // compare two strings
    bool String::operator<=(const String& str) const {
        return (this->s_sLen <= str.s_sLen) ? true : false;
    }
    
    // TODO : REWRITE - NOT FUNCTIONING
    String String::operator+(const char* str) {
        String string;
        string.Alloc(this->s_sLen += len(str));
        string.Concat(this->s_buf, str);
        //std::cout << string << std::endl;
        return string;
    }

    String String::operator+(const String& str) {
        return (*this + str.s_buf);
    }

    String String::operator+=(const char* str) {
        String string(*this);
        this->Alloc(string.s_sLen += len(str));
        this->Concat(string.s_buf, str);
        return *this;
    }

    String String::operator+=(const String& str) {
        return (*this += str.s_buf);
    }

    // TODO : ERROR HANDLING
    void String::Concat(const String& str) {
        if (str.s_sLen > (this->s_bLen - this->s_sLen)) {
            /*int sLength = (s_sLen + str.s_s_len);
            int bLength = (s_bLen + str.s_bLen);
            char* t_buf = new char[bLength + 1];
            t_buf[bLength] = '\0';
            FillTo(t_buf, 0, this->s_sLen);
            str.FillTo(t_buf, this->s_sLen, str.s_sLen);
            Alloc(bLength);
            s_sLen = sLength;
            FillFrom(t_buf, 0, ??);*/
        }
        else {
            for (int i = 0, iter = s_sLen; i < str.s_sLen; iter++, i++) {
                this->s_buf[iter] = str.s_buf[i];
                ++s_sLen;
            }
        }
    }

    // concatenate two c-strings
    void String::Concat(const char* str1, const char* str2) {
        // len1 = length of first string, len2 = length of second string
        int len1 = len(str1), len2 = len(str2);
        // fill first part of string with c-string
        for (iter = 0; iter < len1; iter++) {
            s_buf[iter] = str1[iter];
        }
        // fill second part of string with second c-string
        for (int i = 0; i < len2; i++, iter++) {
            s_buf[iter] = str2[i];
        }
    }

    String String::Substr(int in1, int in2) {
        if (in1 >= 0 && in2 < s_sLen && in1 <= in2) {
            char* buff = new char[((in2 - in1)+1) + 1]();
            for (int i = 0, iter = in1; iter <= in2; iter++, i++) {
                buff[i] = s_buf[iter];
            }
            String string(buff);
            delete buff;
            return string;
        }
    }

    // fill buffer with c-string
    void String::FillFrom(const char* str) {
        for (iter = 0; iter < s_sLen; iter++) {
            this->s_buf[iter] = str[iter];
        }
    }

    void String::FillTo(char* str) const {
        for (iter = 0; iter < s_sLen; iter++) {
            str[iter] = this->s_buf[iter];
        }       
    }

    // TODO: HANDLE OUT OF RANGE
    // subscript operator
    char& String::operator[](const int index) const {
        // if desired index isn't out of range
        // return reference to value
        if (index >= 0 && index < s_sLen) {
            return s_buf[index];
        }
        // else return null

    }

    // allocate space for string
    void String::Alloc(int len) {
        // check if new length is positive
        if (len >= 0) {
            // deallocate if string is full already
            if (s_sLen > 0) {
                Dealloc();
            }
            // allocate if new length is greater than 0
            if (len != 0) {
                s_bLen = len;
                s_buf = new char[s_bLen + 1];
                Term();
            }
        }
    }

    // deallocate string space
    void String::Dealloc() {
        // deallocate if buffer is full
        if (s_bLen > 0 && s_buf != NULL) {
            s_sLen = 0;
            s_bLen = 0;
            delete [] s_buf;
            s_buf = NULL;
        }
    }

    // TODO: needs work
    void String::Term() {
        for (iter = 0; iter <= s_bLen; iter++) {
            s_buf[iter] = '\0';
        }
    }

    
    // Public mutators
    void String::Reverse() {
        // used for temp storage of character
        char temp;
        for (int i = 0, j = s_sLen - 1; i <= j; i++, j--) {
            temp = s_buf[i];
            s_buf[i] = s_buf[j];
            s_buf[j] = temp;
        }
    }

    // replace char at index with new char
    void String::Replace(int in, char ch) {
        if (in >= 0 && in < s_sLen) {
            this->s_buf[in] = ch;
        }
        else {
            std::cerr << "Operation Aborted: Boundary Error" << std::endl;
        }
    }

    // replace specified range with a new string
    void String::Replace(int b_In, int e_In, const char* str) {
        // first get length of cstring
        int slen = len(str);
        // if indices are within bounds and in order
        if (b_In >= 0 && e_In < s_sLen && b_In <= e_In) {
            // iterate starting at b_in and beginning of cstring
            for (int i = 0, iter = b_In; iter <= e_In && i < slen; ++iter, ++i) {
                this->s_buf[iter] = str[i];
            }
        }
    } // Replace (int, int, const char*)

    // Delete a single char *calls overloaded delete for deleting range
    void String::Delete(int in) {
        // single character so range is in to in
        Delete(in, in);
    }

    // Delete a range of characters from in1 to in2 inclusive!
    void String::Delete(int in1, int in2) {
        // boundary checking
        if (in1 >= 0 && in1 <= in2 && in2 < s_sLen) {
            int range = ((in2 - in1) + 1);
            // first assign as much to range from left over after range as possible
            for (int i = in1, j = (in2 + 1); i <= in2, j < s_sLen; i++, j++) {
                s_buf[i] = s_buf[j];
            }
            // now null terminate leftover for cases where range and leftover are not equal
            for (int i = (s_sLen - range); i < s_sLen; i++) {
                s_buf[i] = '\0';
            }
            // now update string length
            s_sLen -= range;
        }
    }

    // Append a character to the end of the string
    void String::Append(char ch) {
        Insert((s_sLen - 1), ch);
    } // APPEND(CHAR)

    void String::Prepend(char ch) {
        Insert(0, ch);
    }

    // insert a char at a specified index
    bool String::Insert(int in, char ch) {
        // make sure index is within bounds
        if (in >= 0 && in < s_sLen) {
            // must reallocate if inserting a char will cause overflow
            if ((s_sLen + 1) > s_bLen) {
                int sLength = s_sLen;                                           // maintain string length
                int bLength = s_bLen + REALLOC_BY;                              // buffer length is orig buff plus modifier
                char* t_buf = new char[bLength + 1];                            // allocate a tempory buffer to store string contents
                t_buf[bLength] = '\0';                                          // null terminate temp buff
                FillTo(t_buf);                                                  // fill temporary buffer with string contents
                Alloc(bLength);                                                 // reallocate string
                s_sLen = sLength;                                               // restore string length after reallocation
                FillFrom(t_buf);                                                // fill string from buffer
                delete t_buf;                                                   // cleanup buffer
            }
            if (s_sLen != 0){
                ++s_sLen;                                                           // increment string length by 1
                for (iter = (s_sLen - 1); iter > in; iter--) {
                    s_buf[iter] = s_buf[iter - 1];                                  // shift all contents to right of index
                }
                s_buf[in] = ch;                                                     // now insert char
            }
            else {
                ++s_sLen;
                s_buf[0] = ch;
            }
        }
        // TODO: OUT OF INDEX HANDLE
        else {
            return 0;
        }
        return 1;
    } // INSERT(INT, CHAR)

    // Capitalize every letter in the string
    bool String::Upper() {
        // call overloaded Upper() with range of entire string
        return this->Upper(0, (s_sLen - 1));
    } // UPPER

    // capitalize specific character
    bool String::Upper(int in) {
        // call overloaded Upper() with range of in to in (one char)
        return this->Upper(in, in);
    }

    // capitalize all letters
    // used for overloaded methods
    bool String::Upper(int in1, int in2) {
        if (in1 <= in2 && in2 < s_sLen) {
            for (iter = in1; iter <= in2; iter++) {
                if (isAlpha(s_buf[iter]) && isLower(s_buf[iter])) {
                    s_buf[iter] = (s_buf[iter] - CASEDIFF);
                }
            }
            return true;
        }
        else
            return false;
    }

    // set all characters to lowercase
    bool String::Lower() {
        return this->Lower(0, (s_sLen - 1));
    }

    // set specific character to lowercase
    bool String::Lower(int in) {
        return this->Lower(in, in);
    }

    // set range of characters to lowercase
    // used for other methods
    bool String::Lower(int in1, int in2) {
        if (in1 <= in2 && in2 < s_sLen) {
            for (iter = in1; iter <= in2; iter++) {
                if (isAlpha(s_buf[iter]) && isUpper(s_buf[iter])) {
                    s_buf[iter] = (s_buf[iter] + CASEDIFF);
                }
            }
            return true;         
        }
        else
            return false;
    }

    // Public accessors
    int String::Length() const {
        return s_sLen;
    }

    int String::End() const {
        return (s_sLen - 1);
    }

    char String::CharAt(int in) const {
        if (in >=0 && in < s_sLen) return s_buf[in];
    }

    char* String::GetBuff() const {
        return s_buf;
    }

    // Print with help from a friend
    std::ostream& operator<<(std::ostream& ost, const String& str) {
        return ost << str.s_buf;
    }

    // helper methods
    int String::len(const char* str) const {
        int i;
        for (i = 0; str[i] != '\0'; i++) {}
        return i;
    }

    // check if character is alphabetical
    bool String::isAlpha(const char ch) const {
        return ((int(ch) >= CAP_BEG && int(ch) <= CAP_END
                 || int(ch) >= LOW_BEG && int(ch) <= LOW_END)) ? true : false;
    }

    // check if character is uppercase
    bool String::isUpper(const char ch) const {
        return ((isAlpha(ch) && ch <= CAP_END)) ? true : false;
    }

    // check if character is lowercase
    bool String::isLower(const char ch) const {
        return ((isAlpha(ch) && ch >= LOW_BEG)) ? true : false;
    }
}