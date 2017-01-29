#include <iostream>
#include "String.h"

int main (int argc, char*argv[]) {
	Comet::String str(80);
	str = "HEY DUDES";
	Comet::String str2(str.Substr(0, 4));
	std::cout << str2 << std::endl;
	str.Concat(str2.Substr(0, 2));
	std::cout << str << std::endl;
	return 1;
}
