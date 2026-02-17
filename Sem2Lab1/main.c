#include <stdio.h>
#include "functions.h"

int main(int argc, char* argv[])
{
	char* filename;
	create_filename(&filename, argv[1]);

	FILE* bin_file;

	menu(&bin_file, filename);

	return 0;
}