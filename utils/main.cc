#include <iostream>
#include "String.h"

int main (int argc, char*argv[]) {
	Comet::String str4;
	Comet::String str("hey dude");
	str4 = "H";
	str4 += "HELLO";
	str4.Append(str);
	std::cout << str4 << std::endl;
	return 1;
}
