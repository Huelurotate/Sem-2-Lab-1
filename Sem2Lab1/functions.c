#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "functions.h"

void create_filename(char** filename_var, char* user_input)
{
	if (user_input != NULL)
	{
		*filename_var = malloc(strlen(user_input) + 1);
		strcpy_s(*filename_var, strlen(user_input) + 1, user_input);
	}
	else
	{
		*filename_var = NULL;
	}

	check_filename(filename_var);
}

void check_filename(char** filename)
{
	int len;
	while (1)
	{
		len = (*filename == NULL) ? 0 : strlen(*filename);

		if (len >= EXTENSION_LEN && strcmp(".bin", (*filename + (len - EXTENSION_LEN))) == 0)
			break;

		puts("Please, enter a filename with a .bin extension:");
		filename_input(filename, &len);
	}
}

void filename_input(char** str, int* length)
{
	*length = 0;
	char c;
	while ((c = getchar()) != '\n')
	{
		(*length)++;
		*str = realloc(*str, (*length + 1) * sizeof(char));
		(*str)[*length - 1] = c;
	}

	(*str)[*length] = '\0';
}

void menu(FILE** file, char* filename)
{
	int menu_choice, is_running = 1;
	int total_numbers = 0;

	srand(time(NULL));

	while (is_running)
	{
		print_menu();
		option_choice(&menu_choice);
		switch (menu_choice)
		{
		case 1:
			input(file, filename, &total_numbers);
			break;
		case 2:
			if (total_numbers != 0)
				output(file, filename, total_numbers);
			else
				puts("\nThe file is empty.");
			break;
		case 3:
			if (total_numbers != 0)
				continue;
			else
				puts("\nThe file is empty.");
			break;
		case 4:
			// free_str(str, &length);
			is_running = 0;
		}
	}
}

void print_menu()
{
	puts("\n      MENU\n"
		"Choose an option:\n"
		"1 - Input Data\n"
		"2 - Output Data\n"
		"3 - Add Numbers To The File\n"
		"4 - Reverse File Contents\n"
		"5 - Exit Program");
}

void option_choice(int* choice)
{
	while (scanf_s("%d", choice) != 1 || \
		(*choice != 1 && *choice != 2 && *choice != 3 && *choice != 4))
	{
		puts("Invalid Input.");
		rewind(stdin);
	}
}

void input(FILE** file, char* filename, int* total_numbers)
{
	int user_input_choice = WRITE_CHOICE;
	int user_random_choice;

	if (*total_numbers != 0)
		input_choice(&user_input_choice);

	random_choice(&user_random_choice);

	if (user_random_choice)
		random_input(file, filename, total_numbers, user_input_choice);
	else
		manual_input(file, filename, total_numbers, user_input_choice);
}

void manual_input(FILE** file, char* filename, int* total_numbers, int user_input_choice)
{
	if ((*total_numbers > 0 && user_input_choice == WRITE_CHOICE) || *total_numbers == 0)
		*file = fopen(filename, "wb");
	else
		*file = fopen(filename, "ab");

	file_opening_check(*file);
	
	while (1)
	{
		getchar();

		puts("\nEnter a number to put into the file:");

		char char_input = getchar();

		if (char_input == '\n')
			break;

		ungetc(char_input, stdin);

		int num;
		while (scanf_s("%d", &num) != 1)
		{
			puts("Invalid Input.");
			rewind(stdin);
		}

		fwrite(&num, sizeof(int), 1, *file);
		(*total_numbers)++;
	}

	fclose(*file);
}

void random_input(FILE** file, char* filename, int* total_numbers, int user_input_choice)
{
	if ((*total_numbers > 0 && user_input_choice == WRITE_CHOICE) || *total_numbers == 0)
		*file = fopen(filename, "wb");
	else
		*file = fopen(filename, "ab");

	file_opening_check(*file);

	int random_length = (rand() % (RAND_LEN_MAX - RAND_LEN_MIN + 1)) + RAND_LEN_MIN;
	int random_num;

	for (int i = 0; i < random_length; i++)
	{
		random_num = (rand() % (RAND_MAX - RAND_MIN + 1)) + RAND_MIN;
		fwrite(&random_num, sizeof(int), 1, *file);
	}

	*total_numbers += random_length;
	fclose(*file);

	puts("\nRandom numbers have been added to the file.");
}

void input_choice(int* choice)
{
	printf("\nWould like to write or append to the file?(1 - Write, 0 - Append): ");
	choice_loop(choice);
}

void random_choice(int* choice)
{
	printf("\nFill the file with random numbers?(1 - Yes, 0 - No): ");
	choice_loop(choice);
}

void choice_loop(int* choice_var)
{
	while (scanf_s("%d", choice_var) != 1 || (*choice_var != 0 && *choice_var != 1))
	{
		puts("Invalid Input.");
		rewind(stdin);
	}
}

void output(FILE** file, char* filename, int total_numbers)
{
	*file = fopen(filename, "rb");
	file_opening_check(*file);

	int num;

	puts("Contents of the file are:");
	for (int i = 0; i < total_numbers; i++)
	{
		fread(&num, sizeof(int), 1, *file);
		printf("%d\n", num);
	}

	fclose(*file);
}

void count_unique(FILE** file, char* filename, int total_numbers)
{

}

void add_numbers(FILE** file, char* filename, int* total_numbers)
{

}

void perform_reverse(FILE** file, char* filename, int* total_numbers)
{

}

void file_opening_check(FILE* file)
{
	if (file == NULL)
	{
		puts("Failed to open the file.");
		exit(1);
	}
}

void check_arr_alloc(int* arr)
{
	if (arr == NULL)
	{
		puts("Memory Allocation Error.");
		exit(1);
	}
}

