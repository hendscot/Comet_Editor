#include <iostream>
#include "String.h"

int main (int argc, char*argv[]) {
	Comet::String str(80);
	str.Append('#');
	str.Append('i');
	str.Append('n');
	str.Append('c');
	str.Append('l');
	str.Append('u');
	str.Append('d');
	str.Append('e');
	str.Append(' ');
	str.Append('<');
	str.Append('i');
	str.Append('o');
	str.Append('s');
	str.Append('t');
	str.Append('r');
	str.Append('e');
	str.Append('a');
	str.Append('m');
	str.Append('>');
	std::cout << str << std::endl;
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	str.Insert(0, 'a');
	
	std::cout << str << std::endl;

	return 1;
}
