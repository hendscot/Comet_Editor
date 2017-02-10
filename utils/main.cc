#include <iostream>
#include "String.h"

int main (int argc, char*argv[]) {
	Comet::String str("Hey ya'll Dudes is cool");
	str.Insert(str.End(), 'Z');
	std::cout << str << std::endl;
	std::cout << str.Length();
	return 1;
}
