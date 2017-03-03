#include <iostream>
#include "String.h"

int main (int argc, char*argv[]) {
	Comet::String str4;
	str4 = "H";
	str4.Append('a');
	str4.Append('a');
	std::cout << str4 << std::endl;
	return 1;
}
