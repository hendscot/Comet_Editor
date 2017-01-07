#include <cstddef>
#include <iostream>
#include "Line.h"
#include "LineMan.h"

LineMan::LineMan() {
	l_strt = NULL;
	l_end = NULL;
	Newline(); // assume 1 line default
}

LineMan::~LineMan() {

}

void LineMan::Newline() {
	LPTR newL = new Line;
	if (NoLines()) {
		l_strt = l_end = newL;
		l_strt->next = l_end;
	}
	else {
		LPTR iter = l_end;
		l_end = newL;
		iter->next = l_end;
		l_end->prev = iter;
		l_end->next = l_strt;
		l_strt->prev = l_end;
	}
}

void LineMan::Insert(int ln, int in, char ch) {
	LPTR iter = l_strt;
	for (int i = 0; i < ln && iter->next != l_strt; iter = iter->next, i++);
	if (ch != '\n' && iter->str[in] == '\n') {
		iter->str->Insert(in, ch);
		iter->newL = false;
	}
	else if (ch == '\n') {
		iter->str->Insert(in, ch);
		iter->newL = true;
	}
	else {
		iter->str->Insert(in, ch);
	}
}

void LineMan::Append(char ch) {
	LPTR iter = l_strt;
	while (iter->next != l_strt && iter->newL) {
		iter = iter->next;
	}
	if (iter->newL) {
		Newline();
		iter = iter->next; 
	}
	iter->str->Insert(iter->currIn, ch);
	if (ch == '\n')
		iter->newL = true;
	++iter->currIn;
	
}

void LineMan::Delete(int LN, int index) {
    LPTR iter = l_strt;
	for (int i = 0; i < LN && iter->next != l_strt; i++, iter = iter->next);
	iter->str->Delete(index);
}

void LineMan::Display () {
    if (l_strt){
      LPTR iter = l_strt;
      do {
          std::cout << iter->lineNO << " ";
		  std::cout << *iter->str << std::endl;
          iter = iter->next;
      } while (iter != l_strt && iter != NULL);
    }
}

bool LineMan::Full(LPTR ln) {
    if (ln->currIn >= STR_SIZE || ln->str[ln->currIn] == '\n')
        return true;
    else
        return false;
}

bool LineMan::NoLines() {
    return (!l_strt);
}
