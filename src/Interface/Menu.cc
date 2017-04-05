#include <ncurses.h>
#include "../../includes/Interface/Menu.h"

namespace Comet {
    namespace Interface {
        Menu::Menu () {
            PrintMenu ();
        }

        Menu::~Menu () {

        }

    void Menu::PrintMenu () {
            printw( "Welcome to Comet Ghost Text Editor");
        }
    }
}