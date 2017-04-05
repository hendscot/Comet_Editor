#include <cstddef>
#include <ncurses.h>
#include "../../includes/Core/Line.h"
#include "../../includes/Core/LineManager.h"
namespace Comet {
	namespace Core {
		// No param constructor - intialize pointers, create new line
		LineManager::LineManager() :
		 strt_ = NULL, end_ = NULL  {
			Newline();
		}
		// Destructor, calls self destruct method
		LineManager::~LineManager() {
			SelfDestruct ();
		}
		// creates a new Line node in sequence (appends to end of list)
		void LineManager::Newline() {
			LPTR newL = new Line;
			if (NoLines()) { 
				strt_ = end_ = newL;
				strt_->next = end_;
				strt_->prev = end_;
			}
			else {
				iter_ = end_;
				end_ = newL;
				iter_->next = end_;
				end_->prev = iter_; 
				end_->next = strt_;
				strt_->prev = end_;
			}
		} // NEWLINE ()

		// Can be used to attach to beginning or insert within
		void LineManager::InsertLineBefore(LPTR LN) {
			if (NoLines()) {
				Newline();
			}
			else if (LN == strt_) {
				LPTR newL = new Line;
				newL->next = strt_;
				newL->prev = strt_->prev;
				strt_->prev = newL;
				strt_ = newL;
			}
			else {
				LPTR newL = new Line;
				newL->prev = LN->prev;
				newL->next = LN;
				LN->prev->next = newL;
				LN->prev = newL;
			}
		} // INSERTLINEBEFORE (LPTR)

		// Can be used to append to end (by calling Newline) or can be used to insert within
		void LineManager::InsertLineAfter(LPTR LN) {
			// if no lines exist or we're at the end, Newline method can be used
			if (NoLines() || LN == end_) {
				Newline();
			}
			else {
				// we must be in the middle so just rearrange pointers...
				LPTR newL               = new Line;					    
				newL->prev              = LN;
				newL->next              = LN->next;
				newL->next->prev        = newL;
				LN->next                = newL;
			}
		} // INSERTLINEAFTER (LPTR)
		// TODO: INSERT CODE TO PREVENT ACCESS OF NONEXISTENT LINE NUMBER (POSSIBLY CALL NEWLINE METHOD?)
		void LineManager::InsertChar(const int ln, const int in, char ch) {
			int i;
			// iterate lines from beginning
			iter_ = strt_;                          
			// iterate while not at target line
			for (i = 0; i < ln; iter_ = iter_->next, i++);     					  
			if (i == ln) {
				iter_->str->Insert(in, ch);
				++iter_->size;
			}
		} // INSERTCHAR (INT, INT, CHAR)

		// used specifically for handling line break input
		void LineManager::InsertBreak(const int ln, const int in) {
			int i;
			iter_ = strt_;
			for (i = 0; i < ln; iter_ = iter_->next, i++);
			if (i == ln) {
				// if not at end of line will have to move remaining
				if (in <= (iter_->End())) {                                             
					InsertLineAfter(iter_);
					iter_ = iter_->next;
					iter_->str->Append(iter_->prev->str->Substr(in, (iter_->prev->End() - in) + 1));
					iter_->prev->str->Delete(in, iter_->prev->End());
				}
				else {
					InsertLineAfter(iter_);
					iter_ = iter_->next;
				}
				iter_->size = iter_->Length();
				iter_->newL = true;
			}
		} // INSERTBREAK (INT, INT, CH)
		// TODO: ADD METHOD FOR INSERTING ENTIRE STRINGS FOR LESS FUNCTION CALLS

		// TODO this will be modified to take an entire buffer and build from that
		void LineManager::Append(char ch) {
			iter_ = strt_;
			// iterate while valid and newline char exists
			while (iter_->next != strt_ && iter_->newL) {
				iter_ = iter_->next;
			}
			if (iter_->newL) {
				// insert new line node at end
				Newline();
				iter_ = iter_->next;
			}
			// if ch is a newline char
			if (ch == '\n') {
				iter_->newL = true;
			}
			else {
				// insert a ch at curr string index
				(iter_->str->Append(ch));
				++iter_->currIn;
				++iter_->size;
			}
		} // APPEND (CHAR)

		void LineManager::Append(char ch, const int ln) {
			int i;
			 // iterate lines from beginning
			iter_ = strt_;
			// iterate while not at target line and
			for (i = 0; i < ln; iter_ = iter_->next, i++);
			if (i == ln) {
				// insert a ch at curr string index
				(iter_->str->Append(ch));
				++iter_->currIn;
				++iter_->size;
			}
		} // APPEND(CHAR, INT)

		// TODO: HANDLE CONCATENATING LINES
		// delete a character at a specific index and line
		void LineManager::DeleteChar(const int LN, const int index) {
			iter_ = strt_;
			// find target line
			for (int i = 0; i < LN && iter_->next != strt_; i++, iter_ = iter_->next);
			if (index == 0) {
				// delete line if target line is empty
				DeleteLine(iter_);
			}
			else {
				// delete char at index in string
				iter_->str->Delete(index - 1);
				// decrement size
				--iter_->size;
			}
		} // DELETECHAR (INT, INT)

		void LineManager::DeleteLine(LPTR LN) {
			if (LN == end_) {
				if (LN->Length() > 0) {
					ConcatLines(LN);
				}
				end_ = LN->prev;
				end_->next = strt_;
				delete LN;
			}
			else if (LN != strt_ && LN != end_) {
				if (LN->Length() > 0) {
					ConcatLines(LN);
				}
				LN->prev->next = LN->next;
				LN->next->prev = LN->prev;
				delete LN;
			}
		} // DELETELINE (LPTR)

		bool LineManager::Full(LPTR ln) {
			(ln->Length() >= STR_SIZE) ? true : false;
		}

		bool LineManager::NoLines() {
			return (!strt_);
		} //

		void LineManager::SelfDestruct () {
			if (strt_ != NULL) {
				if (strt_->next != NULL) {
					iter_ = strt_;
					while (iter_ != NULL) {
						iter_ = iter_->next;
						delete iter_->prev;
					}
				}
				else {
					delete strt_;
				}
			}
		}

		/* MAKE THESE STATIC?? */
		int LineManager::GetLength (const int LN) const {
			iter_ = strt_;
			// find target line
			for (int i = 0; i < LN && iter_->next != strt_; i++, iter_ = iter_->next);
			return iter_->Length ();
		} // GETLENGTH (INT)

		int LineManager::GetLineCount() const {
			return strt_->lineAmnt;
		} // GETLINECOUNT ()

		int LineManager::ConcatLines (LPTR LN) {
			if (LN->prev->size < 80) {
				int space = (80 - LN->prev->size);
				if (LN->size <= space) {
					LN->prev->str->Append(LN->str->Substr(0, LN->str->Length()));
					LN->prev->size = LN->prev->str->Length();
					return 0;
				}
				else {
					Comet::String sub(LN->str->Substr(0, space));
					LN->str->Delete(0, (space - 1));
					LN->prev->str->Append(sub);
					return 1;
				}
			}
		} // CONCATLINES (LPTR)

		Line* LineManager::First() {
			if (!NoLines()) return strt_;
		}

		void LineManager::Display () const {
		if (strt_){
			iter_ = strt_;
			unsigned lineno = 1;
			do {
			// test if this will work?
			printw("%u ", lineno);
			printw("%s", iter_->str->GetBuff());
			printw("\n");
			iter_ = iter_->next;
			++lineno;
			} while (iter_ != strt_ && iter_ != NULL);
		}
		} // DISPLAY ()

		Line* LineManager::GetStart () const {
			LPTR* tstrt = strt_;
			return tstrt;
		}
	}
}
