#include <iostream>
#include <thread>

void func () {
    std::cout << "This is a thread" << std::endl;
}

int main (int argc, char* argv[]) {
    std::thread t1 (func);
    t1.join ();
}