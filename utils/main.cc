#include <iostream>
#include "String.h"

int main (int argc, char*argv[]) {
	Comet::String str(2);

	str.Insert(0, 'o');
	str.Insert(0, 'l');

	std::cout << str << std::endl;

	return 1;
}
