#include <iostream>
#include "../includes/Core/Line.h"
#include "../includes/Core/LineManager.h"
#include "../includes/IO/Document.h"
#include "../utils/Comet-String/String.h"

int main (int argc, char* argv[]) {
    Ghost::IO::Document::LoadDocument("main.cc");
    Comet::String lines (Ghost::IO::Document::GetBuffer());
    int length = Ghost::IO::Document::GetSize();
    Ghost::IO::Document::CleanUp();
    std::cout << length << std::endl;

    Ghost::Core::LineManager* LM = new Ghost::Core::LineManager();
    for (int i = 0; i < length; i++) {
        LM->Append(lines[i]);
    }
    LM->Display();
}