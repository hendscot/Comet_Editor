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
			l_strt->prev = l_end;                                   
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
		int i;
		LPTR iter = l_strt;                                                          // iterate lines from beginning
		for (i = 0; i < ln && iter->next != l_strt; iter = iter->next, i++);     // iterate while not at target line and 
		if (i == ln) {
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
		if (ch == '\n')																	// if ch is a newline char
			iter->newL = true;	
		else {
			iter->str->Append(ch);											// insert a ch at curr string index
			++iter->currIn;
			++iter->size;
		}
	}
	
	// TODO: HANDLE CONCATENATING LINES
	// delete a character at a specific index and line
	void LineManager::DeleteChar(int LN, int index) {
		LPTR iter = l_strt;
		for (int i = 0; i < LN && iter->next != l_strt; i++, iter = iter->next);        // find target line
		if (index == 0) {
			DeleteLine(iter);															// delete line if target line is empty
		}
		else {
			iter->str->Delete(index - 1);													// delete char at index in string
			--iter->size;																// decrement size
		}
	}

	void LineManager::DeleteLine(LPTR LN) {
		if (LN->lineAmnt > 1) {
			if (1) {
				if (LN->size > 0){
					if (ConcatLines(LN) == 0) {
		        		if (LN != l_end) {
							LN->prev->next = LN->next;
							delete LN;
						}
						else {
							l_end = LN->prev;
							l_end->next = LN->next;
							delete LN;
						}
					}
				}
				else {
					if (LN != l_end) {
						LN->prev->next = LN->next;
						delete LN;
					}
					else {
						l_end = LN->prev;
						l_end->next = LN->next;
						delete LN;
					}
				}
			}
		}
	}

	void LineManager::Display () {
		if (l_strt){
		LPTR iter = l_strt;
		do {
			// test if this will work?
			printw(iter->str->GetBuff());
			printw("\n");
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

	int LineManager::GetLength (int LN) {
		LPTR iter = l_strt;
		for (int i = 0; i < LN && iter->next != l_strt; i++, iter = iter->next);        // find target line
		return iter->Length ();
	}

	int LineManager::GetLineCount() {
		return l_strt->lineAmnt;
	}

	int LineManager::ConcatLines (LPTR LN) {
		if (LN->prev->size < 80) {
			int space = (80 - LN->prev->size);
			if (LN->size <= space) {
				LN->prev->str->Concat(LN->str->Substr(0, LN->str->Length()-1));
				LN->prev->size = LN->prev->str->Length();
				return 0;
			}
			else {
				Comet::String sub(LN->str->Substr(0, (space - 1)));
				//LN->str->Delete(0, (space - 1));
				LN->prev->str->Concat(sub);
				return 1;
			}
		}
	}
}
