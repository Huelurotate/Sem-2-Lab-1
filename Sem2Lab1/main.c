#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(int argc, char* argv[])
{
	char* filename = malloc(strlen(argv[1]) + 1);
	strcpy_s(filename, (strlen(argv[1]) + 1), argv[1]);
	check_filename(&filename);

	FILE* bin_file;

	menu(&bin_file, filename);

	return 0;
}