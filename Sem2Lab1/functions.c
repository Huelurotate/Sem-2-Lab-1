#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

void menu(FILE** file, char* filename)
{
	int menu_choice, is_running = 1;
	int total_numbers = 0;
	int user_random_choice;

	srand(time(NULL));

	while (is_running)
	{
		print_menu();
		option_choice(&menu_choice);
		switch (menu_choice)
		{
		case 1:
			input(file, filename, &total_numbers, &user_random_choice);
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

void check_filename(char** filename)
{
	int len = strlen(*filename);
	while (len < EXTENSION_LEN || strcmp(".bin", (*filename + (len - EXTENSION_LEN))) != 0)
	{
		puts("Please, enter a filename with a .bin extension:");
		filename_input(filename);
		len = strlen(*(filename));
	}
}

void input(FILE** file, char* filename, int* total_numbers, int* user_random_choice)
{
	int user_input_choice = WRITE_CHOICE;

	if (*total_numbers != 0)
		input_choice(&user_input_choice);

	random_choice(user_random_choice);

	if (random_choice)
		random_input(file, filename, total_numbers, user_input_choice);
	else
		manual_input(file, filename, total_numbers, user_input_choice);
}

void manual_input(FILE** file, char* filename, int* total_numbers, int user_input_choice)
{
	if ((total_numbers > 0 && user_input_choice) || total_numbers == 0)
		*file = fopen(filename, "wb");
	else
		*file = fopen(filename, "ab");

	file_opening_check(*file);

	int* buffer = NULL;
	puts("Enter the number to put into the file:");
	while (1)
	{
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

		buffer = realloc(buffer, (*total_numbers) * sizeof(int));
		check_arr_alloc(buffer);
		buffer[(*total_numbers)++] = num;
	}

	fwrite(buffer, sizeof(int), total_numbers, *file);
	free(buffer);
	fclose(file);
}

void random_input(FILE** file, char* filename, int* total_numbers, int user_input_choice)
{
	if ((total_numbers > 0 && user_input_choice) || total_numbers == 0)
		*file = fopen(filename, "wb");
	else
		*file = fopen(filename, "ab");

	file_opening_check(*file);

	int random_length = (rand() % (RAND_LEN_MAX - RAND_LEN_MIN + 1)) + RAND_LEN_MIN;

	int* buffer = malloc(sizeof(int) * random_length);
	check_arr_alloc(buffer);

	for (int i = 0; i < random_length; i++)
	{
		buffer[i] = (rand() % (RAND_MAX - RAND_MIN + 1)) + RAND_MIN;
	}

	fwrite(buffer, sizeof(int), random_length, *file);
	free(buffer);
	fclose(file);
}

void input_choice(int* choice)
{
	printf("Would like to write or append to the file?(1 - Write, 0 - Append): ");
	choice_loop(&choice);
}

void random_choice(int* choice)
{
	printf("\nFill the file with random numbers?(1 - yes, 0 - no): ");
	choice_loop(&choice);
}

void choice_loop(int** choice_var)
{
	while (scanf_s("%d", *choice_var) != 1 || (**choice_var != 0 && **(choice_var) != 1))
	{
		puts("Invalid Input.");
		rewind(stdin);
	}
}

void output(FILE** file, char* filename, int total_numbers)
{
	*file = fopen(filename, "rb");
	file_opening_check(*file);

	int* buffer = malloc(sizeof(int) * total_numbers);
	check_arr_alloc(buffer);

	fread(buffer, sizeof(int), total_numbers, *file);

	puts("Contents of the file are:");
	for (int i = 0; i < total_numbers; i++)
		printf("%d\n", buffer[i]);

	free(buffer);
	fclose(file);
}

void add_numbers(FILE** file, char* filename, int* total_numbers)
{

}

void perform_reverse(FILE** file, char* filename, int* total_numbers)
{

}

void filename_input(char** str)
{
	getchar();

	int length = 0;
	char c;
	while ((c = getchar()) != '\n')
	{
		length++;
		*str = realloc(*str, (length + 1) * sizeof(char));
		(*str)[length - 1] = c;
	}

	(*str)[length] = '\0';
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