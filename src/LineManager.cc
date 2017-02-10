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
	// creates a new Line node in sequence (appends to end of list)
	void LineManager::Newline() {
		LPTR newL = new Line;                                        // allocate space for new line node
		if (NoLines()) {                                             // check if any lines exist 
			l_strt = l_end = newL;									 // point both the beginning and end to the newly allocated line
			l_strt->next = l_end; 
			l_strt->prev = l_end;                                   
		}
		else {                                                       // at least one line must exist
			l_iter = l_end;                                       // hold address of l_end
			l_end = newL;                                            // set l_end equal to the new line
			l_iter->next = l_end;                                      // point old end next to new end
			l_end->prev = l_iter;                                      // point new end previous to old end
			l_end->next = l_strt;                                    // set new end next to beginning of list
			l_strt->prev = l_end;                                    // set start previous to new end
		}
	} // NEWLINE ()

	// Can be used to attach to beginning or insert within
	void LineManager::InsertLineBefore(LPTR LN) {
		if (NoLines()) {											// if list is empty, just call Newline method
			Newline();
		}
		else if (LN == l_strt) {									// if need to insert before a given line and line is first line
			LPTR newL = new Line;									// this won't likely happen for this use, but to be safe...
			newL->next = l_strt;									// the new node's next will point to current head, prev to current
			newL->prev = l_strt->prev;								// tail then rearrange pointers as expected
			l_strt->prev = newL;
			l_strt = newL;
		}
		else {
			LPTR newL = new Line;                                   // We must be in the middle so just rearrange pointers as expected
			newL->prev = LN->prev;
			newL->next = LN;
			LN->prev->next = newL;
			LN->prev = newL;
		}
	} // INSERTLINEBEFORE (LPTR)

	// Can be used to append to end (by calling Newline) or can be used to insert within
	void LineManager::InsertLineAfter(LPTR LN) {
		if (NoLines() || LN == l_end) {								// if no lines exist or we're at the end, Newline method can be used
			Newline();
		}
		else {
			LPTR newL               = new Line;					    // we must be in the middle so just rearrange pointers...
			newL->prev              = LN;
			newL->next              = LN->next;
			newL->next->prev        = newL;
			LN->next                = newL;
		}
	} // INSERTLINEAFTER (LPTR)
	// TODO: INSERT CODE TO PREVENT ACCESS OF NONEXISTENT LINE NUMBER (POSSIBLY CALL NEWLINE METHOD?)
	void LineManager::InsertChar(int ln, int in, char ch) {
		int i;
		l_iter = l_strt;                                                          // iterate lines from beginning
		for (i = 0; i < ln; l_iter = l_iter->next, i++);     					  // iterate while not at target line and 
		if (i == ln) {
			l_iter->str->Insert(in, ch);										  // insert char at desired loc
			++l_iter->size;
		}
	} // INSERTCHAR (INT, INT, CHAR)

	// used specifically for handling line break input
	void LineManager::InsertBreak(int ln, int in) {
		int i;
		l_iter = l_strt;
		for (i = 0; i < ln; l_iter = l_iter->next, i++);
		if (i == ln) {
			if (in <= (l_iter->End())) {                                             // if not at end of line will have to move remaining
				InsertLineAfter(l_iter);										   // chars to next line
				l_iter = l_iter->next;
				l_iter->str->Concat(l_iter->prev->str->Substr(in, l_iter->prev->End()));
				l_iter->size = l_iter->Length();
				l_iter->prev->str->Delete(in, l_iter->prev->End());
				
			}
			else {
				InsertLineAfter(l_iter);
				l_iter = l_iter->next;
			}
			l_iter->newL = true;
		} 
	} // INSERTBREAK (INT, INT, CH)
	// TODO: ADD METHOD FOR INSERTING ENTIRE STRINGS FOR LESS FUNCTION CALLS

	// used for building a document of lines from a file, adds characters one by one
	// should not be called for inserting characters from input
	void LineManager::Append(char ch) {
		l_iter = l_strt;
		while (l_iter->next != l_strt && l_iter->newL) {									// l_iterate while valid and newline char exists
			l_iter = l_iter->next;
		}
		if (l_iter->newL) {
			Newline(); 																	// insert new line node at end
			l_iter = l_iter->next; 
		}
		if (ch == '\n') {
			l_iter->newL = true;
		}																	// if ch is a newline char
		else {
			l_iter->str->Append(ch);											// insert a ch at curr string index
			++l_iter->currIn;
			++l_iter->size;
		}
	} // APPEND (CHAR)

	void LineManager::Append(char ch, int ln) {
		int i;
		l_iter = l_strt;                                                          // l_iterate lines from beginning
		for (i = 0; i < ln; l_iter = l_iter->next, i++);     							 // l_iterate while not at target line and 
		if (i == ln) {
			l_iter->str->Append(ch);
			++l_iter->size;
		}
	} // APPEND(CHAR, INT)
	
	// TODO: HANDLE CONCATENATING LINES
	// delete a character at a specific index and line
	void LineManager::DeleteChar(int LN, int index) {
		l_iter = l_strt;
		for (int i = 0; i < LN && l_iter->next != l_strt; i++, l_iter = l_iter->next);        // find target line
		if (index == 0) {
			DeleteLine(l_iter);															// delete line if target line is empty
		}
		else {
			l_iter->str->Delete(index - 1);													// delete char at index in string
			--l_iter->size;																// decrement size
		}
	} // DELETECHAR (INT, INT)

	void LineManager::DeleteLine(LPTR LN) {
		if (LN == l_end) {
			if (LN->Length() > 0) {
				ConcatLines(LN);
			}
			l_end = LN->prev;
			l_end->next = l_strt;
			delete LN;
		}
		else if (LN != l_strt && LN != l_end) {
			if (LN->Length() > 0) {
				ConcatLines(LN);
			}
			LN->prev->next = LN->next;
			LN->next->prev = LN->prev;
			delete LN;
		}
	} // DELETELINE (LPTR)

	bool LineManager::Full(LPTR ln) {
		if (ln->currIn >= STR_SIZE || ln->str[ln->currIn] == '\n')
			return true;
		else
			return false;
	}

	bool LineManager::NoLines() {
		return (!l_strt);
	} // 

	void LineManager::SelfDestruct () {
		if (l_strt != NULL) {
			if (l_strt->next != NULL) {
				l_iter = l_strt;
				while (l_iter != NULL) {
					l_iter = l_iter->next;
					delete l_iter->prev;
				}
			}
			else {
				delete l_strt;
			}
		}
	}

	/* MAKE THESE STATIC?? */
	int LineManager::GetLength (int LN) {
		l_iter = l_strt;
		for (int i = 0; i < LN && l_iter->next != l_strt; i++, l_iter = l_iter->next);        // find target line
		return l_iter->Length ();
	} // GETLENGTH (INT)

	int LineManager::GetLineCount() {
		return l_strt->lineAmnt;
	} // GETLINECOUNT ()

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
	} // CONCATLINES (LPTR)

	Line* LineManager::First() {
		if (!NoLines()) return l_strt;
	}

	void LineManager::Display () {
      if (l_strt){
        l_iter = l_strt;
        do {
          // test if this will work?
          printw(l_iter->str->GetBuff());
          printw("\n");
          l_iter = l_iter->next;
        } while (l_iter != l_strt && l_iter != NULL);
      }
	} // DISPLAY ()
}
