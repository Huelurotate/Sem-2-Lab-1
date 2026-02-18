#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char* argv[])
{
	char* filename;
	create_filename(&filename, argv[1]);

	menu(filename);

	free(filename);

	return 0;
}