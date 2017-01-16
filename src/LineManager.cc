#include <cstddef>
#include <iostream>
#include <ncurses.h>
#include "Line.h"
#include "LineManager.h"

namespace Comet {
	// No param constructor - intialize pointers, create new line
	LineManager::LineManager() {
		l_strt = NULL;                                               // point l_strt to null
		l_end = NULL;                                                // point l_end to null
		Newline();                                                   // assume 1 line default
	}
	// Destructor, calls self destruct method
	LineManager::~LineManager() {
		SelfDestruct ();
	}
	// creates a new Line node in sequence
	void LineManager::Newline() {
		LPTR newL = new Line;                                        // allocate space for new line node
		if (NoLines()) {                                             // check if any lines exist 
			l_strt = l_end = newL;									 // point both the beginning and end to the newly allocated line
			l_strt->next = l_end;                                    
		}
		else {                                                       // at least one line must exist
			LPTR iter = l_end;                                       // hold address of l_end
			l_end = newL;                                            // set l_end equal to the new line
			iter->next = l_end;                                      // point old end next to new end
			l_end->prev = iter;                                      // point new end previous to old end
			l_end->next = l_strt;                                    // set new end next to beginning of list
			l_strt->prev = l_end;                                    // set start previous to new end
		}
	}
	// TODO: INSERT CODE TO PREVENT ACCESS OF NONEXISTENT LINE NUMBER (POSSIBLY CALL NEWLINE METHOD?)
	void LineManager::InsertChar(int ln, int in, char ch) {
		LPTR iter = l_strt;                                                          // iterate lines from beginning
		for (int i = 0; i < ln && iter->next != l_strt; iter = iter->next, i++);     // iterate while not at target line and 
		if ((i + 1) == ln) {
			if (ch != '\n' && iter->str[in] == '\n') {                               // if insert ch is not a newline and current index is newline
				iter->str->Insert(in, ch);                                           // insert new ch at current index
				iter->newL = false;													 // set newL exists to false
				++iter->size;                                                        // increment size
			}
			else if (ch == '\n') {													 // check if new character is a newline
				iter->str->Insert(in, ch);
				iter->newL = true;
			}
			else {
				iter->str->Insert(in, ch);
				++iter->size;
			}
		}
	}
	// TODO: ADD METHOD FOR INSERTING ENTIRE STRINGS FOR LESS FUNCTION CALLS

	// used for building a document of lines from a file, adds characters one by one
	void LineManager::Append(char ch) {
		LPTR iter = l_strt;
		while (iter->next != l_strt && iter->newL) {									// iterate while valid and newline char exists
			iter = iter->next;
		}
		if (iter->newL) {
			Newline(); 																	// insert new line node at end
			iter = iter->next; 
		}
		iter->str->Insert(iter->currIn, ch);											// insert a ch at curr string index
		if (ch == '\n')																	// if ch is a newline char
			iter->newL = true;	
		else {
			++iter->currIn;
			++iter->size;
		}
	}
	// delete a character at a specific index and line
	void LineManager::DeleteChar(int LN, int index) {
		LPTR iter = l_strt;
		for (int i = 0; i < LN && iter->next != l_strt; i++, iter = iter->next);        // find target line
		if (iter->size == 0) {
			DeleteLine(iter);															// delete line if target line is empty
		}
		else {
			iter->str->Delete(index);													// delete char at index in string
			--iter->size;																// decrement size
		}
	}

	void LineManager::DeleteLine(LPTR ln) {
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

	void LineManager::Display () {
		if (l_strt){
		LPTR iter = l_strt;
		do {
			// test if this will work?
			printw(iter->str->GetBuff());
			iter = iter->next;
		} while (iter != l_strt && iter != NULL);
		}
	}


	bool LineManager::Full(LPTR ln) {
		if (ln->currIn >= STR_SIZE || ln->str[ln->currIn] == '\n')
			return true;
		else
			return false;
	}

	bool LineManager::NoLines() {
		return (!l_strt);
	}

	void LineManager::SelfDestruct () {
		if (l_strt != NULL) {
			if (l_strt->next != NULL) {
				LPTR iter = l_strt;
				while (iter != NULL) {
					iter = iter->next;
					delete iter->prev;
				}
			}
			else {
				delete l_strt;
			}
		}
	}
}