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

void LineMan::Newline () {
    LPTR newL = new Line;
    if (NoLines()) {
        l_strt = l_end = newL;
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

void LineMan::Insert(char ch, int in, int ln) {
  bool full = true;
  LPTR iter = (l_strt + (ln - 1));
  if (Full(iter)) {
    char save = iter->chr[iter->currIn];
    iter->ShiftRight();
    iter->chr[in] = ch;
    while (full){
      if (iter->next != l_strt){
        if (iter->currIn >= CHMAX) {
          
        }
      }
      else {
        Newline();
        full = false;
      }
    }
  }
}

void LineMan::Append (char ch) {
    LPTR iter = l_strt;
    while (Full(iter)) {
        if (iter->next && iter->next != l_strt)
            iter = iter->next;
        else {
            Newline();
            iter = iter->next;
        }
    }
    iter->chr[iter->currIn] = ch;
    if (ch != '\n') iter->currIn++;
    // ++iter->size;
}

void LineMan::Delete(int LN, int index) {
    LPTR iter = l_strt;
    if (index >= (CHMAX-1)) {
        for (int i = 1; i <= LN; i++) {
            iter = iter->next;
        }
        iter->chr[CHMAX-1] = '\0';
    }
}

void LineMan::Display () {
    if (l_strt){
      LPTR iter = l_strt;
      do {
          std::cout << iter->lineNO << " ";
          for (int i = 0; i < CHMAX; i++) {
              std::cout << iter->chr[i];
          }
          std::cout << std::endl;
          iter = iter->next;
      } while (iter != l_strt && iter != NULL);
    }
}

bool LineMan::Full(LPTR ln) {
    if (ln->currIn >= CHMAX || ln->chr[ln->currIn] == '\n')
        return true;
    else
        return false;
}

bool LineMan::NoLines() {
    return (!l_strt);
}
