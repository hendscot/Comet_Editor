#include "Menu.h"
#include <ncurses.h>

namespace Comet {
    Menu::Menu () {
        PrintMenu ();
    }

    Menu::~Menu () {

    }

   void Menu::PrintMenu () {
        printw( "Welcome to Comet Ghost Text Editor");
    }
}