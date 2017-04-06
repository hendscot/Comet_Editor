#include "../includes/Interface/Editor.h"
int main (int argc, char* argv[]) {
    auto* ghost = Ghost::Interface::Editor::GetGhostInstance();
    if (argc < 1) {
        std::cerr << "Missing arguments. Operation aborted." << std::endl;
        return 0;
    }
    return ghost->Run();
}