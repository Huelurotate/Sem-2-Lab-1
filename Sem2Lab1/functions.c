#include <stdio.h>

void str_input(char** str)
{
	getchar();

	puts("\nEnter a string:");
	char c;
	while ((c = getchar()) != '\n')
	{
		(*length)++;
		*str = realloc(*str, (*length + 1) * sizeof(char));
		check_str_alloc(*str);
		(*str)[*length - 1] = c;
	}

	(*str)[*length] = '\0';
}