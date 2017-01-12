#include <cstddef>
#include <iostream>
#include <ncurses.h>
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

void LineMan::InsertChar(int ln, int in, char ch) {
	LPTR iter = l_strt;
	for (int i = 0; i < ln && iter->next != l_strt; iter = iter->next, i++);
	if (ch != '\n' && iter->str[in] == '\n') {
		iter->str->Insert(in, ch);
		iter->newL = false;
		++iter->size;
	}
	else if (ch == '\n') {
		iter->str->Insert(in, ch);
		iter->newL = true;
	}
	else {
		iter->str->Insert(in, ch);
		++iter->size;
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
	else {
		++iter->currIn;
		++iter->size;
	}
}

void LineMan::DeleteChar(int LN, int index) {
    LPTR iter = l_strt;
	for (int i = 0; i < LN && iter->next != l_strt; i++, iter = iter->next);
	if (iter->size == 0) {
		DeleteLine(iter);
	}
	else {
		iter->str->Delete(index);
	}
}

void LineMan::DeleteLine(LPTR ln) {
	LPTR iter = l_strt;
	LPTR temp = ln;
	if (ln) {
		if (ln->prev != ln && ln->next != l_strt) {
			ln->prev->next = ln->next;
			for (iter = ln->next; iter != l_strt; iter = iter->next) {
				--iter->lineNO;
			}
			delete temp;
		}
		else {
			delete temp;
			ln = ln->prev = ln->next = NULL;
		}
	}
}

void LineMan::Display () {
    if (l_strt){
      LPTR iter = l_strt;
      do {
		  // test if this will work?
          printw(iter->lineNO);
		  printw(iter->str->GetBuff());
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
