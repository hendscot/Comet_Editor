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
        std::cout << s_sLen << std::endl;
        // use assignment overload to create
        *this = str;
    } // String::String(const char*)

    // Copy Constructor
    String::String(const String& str) 
        : String(str.s_sLen) {
        s_sLen = s_bLen;
        std::cout << s_sLen << std::endl;
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
            Fill(str.s_buf);
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
        Fill(str);
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

    void String::Concat(const String& str) {
        if (str.s_sLen > (this->s_bLen - this->s_sLen)) {

        }
        else {
            for (int i = 0, iter = s_sLen; i < (s_sLen + str.s_sLen); iter++, i++) {
                this->s_buf[iter] = str.s_buf[i];
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

    String& String::Substr(int in1, int in2) {
        if (in1 >= 0 && in2 < s_sLen && in1 <= in2) {
            char* buff = new char[((in2 - in1)+1) + 1]();
            for (int i = 0, iter = in1; iter <= in2; iter++, i++) {
                buff[i] = s_buf[iter];
            }
            String* string = new String(buff);
            delete buff;
            return *string;
        }
    }

    // fill buffer with c-string
    void String::Fill(const char* str) {
        for (iter = 0; iter < s_sLen; iter++) {
            this->s_buf[iter] = str[iter];
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
        int slen = len(str);
        if (b_In >= 0 && b_In < s_sLen && e_In >= 0 && e_In < s_sLen) {
            if (b_In <= e_In) {
                for (int i = 0, iter = b_In; iter <= e_In && i < slen; ++iter, ++i) {
                    this->s_buf[iter] = str[i];
                }
            }
        }
    }

    void String::Delete(int in) {
        for (iter = (in + 1); iter <= s_sLen; iter++) {
            s_buf[iter - 1] = s_buf[iter];
        }
    }

    void String::Append(char ch) {
        if (s_sLen < s_bLen) {
            s_sLen += 1;
            s_buf[(s_sLen - 1)] = ch;
        }
        else {
            char* t_buf = new char[s_bLen + 1];
            t_buf[s_bLen] = '\0';
            Alloc(s_bLen + 10);
            Fill(t_buf);
            delete t_buf;
        }
    }

    bool String::Insert(int in, char ch) {
		bool of = false;
        if ((s_sLen + 1) < s_bLen) {
            ++s_sLen;
        }
        else {
            overflow[0] = s_buf[s_sLen - 1];
			of = true;
        }
        for (iter = (s_sLen - 1); iter > in; iter--) {
            s_buf[iter] = s_buf[iter - 1];
        }
        s_buf[in] = ch;
		return of;
    }

    //
    bool String::Upper() {
        return this->Upper(0, (s_sLen - 1));
    }

    // capitalize specific character
    bool String::Upper(int in) {
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

    char String::Overflow() const {
        return overflow[0];
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