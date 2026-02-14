#include <stdio.h>
#include "functions.h"

int main(int argc, char* argv[])
{
	FILE* bin_file;

	if (!fopen_s(&bin_file, argv[1], "wb"))
	{
		printf("Invalid file name, please try again.");

		char* new_filename;
		str_input(&new_filename);

		main(2, new_filename);
	}

	getchar();

	fclose(bin_file);

	return 0;
}