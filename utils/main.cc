#include <iostream>
#include "FileHandler.h"

int main (int argc, char*argv[]) {
	FileHandler fh;
	fh.Read("./test.txt");
	fh.Write("t.txt");

	return 1;
}
