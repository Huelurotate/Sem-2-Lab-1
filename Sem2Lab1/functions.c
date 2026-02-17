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
				count_unique(file, filename, total_numbers);
			else
				puts("\nThe file is empty.");
			break;
		case 4:
			if (total_numbers != 0)
				insert_numbers(file, filename, &total_numbers);
			else
				puts("\nThe file is empty.");
			break;
		case 5:
			if (total_numbers != 0)
				perform_reverse(file, filename, total_numbers);
			else
				puts("\nThe file is empty.");
			break;
		case 6:
			is_running = 0;
		}
	}
}

void print_menu()
{
	puts("\n      MENU\n"
		"Choose an option:\n"
		"1 - Input Numbers\n"
		"2 - Print File Contents\n"
		"3 - Count Unique Numbers\n"
		"4 - Insert Numbers Into The File\n"
		"5 - Reverse File Contents\n"
		"6 - Exit Program");
}

void option_choice(int* choice)
{
	while (scanf_s("%d", choice) != 1 || \
		(*choice != 1 && *choice != 2 && *choice != 3 && \
			*choice != 4 && *choice != 5 && *choice != 6))
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


// SOMETHING DOES NOT WORK
void manual_input(FILE** file, char* filename, int* total_numbers, int user_input_choice)
{
	int last_element;

	if ((*total_numbers > 0 && user_input_choice == WRITE_CHOICE) || *total_numbers == 0)
	{
		*file = fopen(filename, "wb");
		*total_numbers = 0;
		last_element = NULL;
	}
	else
	{
		*file = fopen(filename, "ab+");
		find_last_element(file, &last_element);
	}

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
		while (scanf_s("%d", &num) != 1 || \
			(last_element != NULL && num > last_element))
		{
			printf("Invalid Input. Enter a number less or equal to %d\n", last_element);
			rewind(stdin);
		}

		last_element = num;

		fwrite(&num, sizeof(int), 1, *file);
		(*total_numbers)++;
	}

	fclose(*file);
}

void random_input(FILE** file, char* filename, int* total_numbers, int user_input_choice)
{
	int max_num;

	if ((*total_numbers > 0 && user_input_choice == WRITE_CHOICE) || *total_numbers == 0)
	{
		*file = fopen(filename, "wb");
		*total_numbers = 0;
		max_num = RAND_MAX;
	}
	else
	{
		*file = fopen(filename, "ab+");
		find_last_element(file, &max_num);
	}

	file_opening_check(*file);

	int random_length = (rand() % (RAND_LEN_MAX - RAND_LEN_MIN + 1)) + RAND_LEN_MIN;
	int random_num;

	for (int i = 0; i < random_length; i++)
	{
		random_num = (rand() % (max_num - RAND_MIN + 1)) + RAND_MIN;
		fwrite(&random_num, sizeof(int), 1, *file);
		max_num = random_num;
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

void find_last_element(FILE** file, int* last_element_var)
{
	fseek(*file, (0 - sizeof(int)), SEEK_END);
	fread(last_element_var, sizeof(int), 1, *file);
	fseek(*file, 0, SEEK_END);
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
	file = fopen(filename, "rb");
	int previous_num, current_num, total_unique = 1;

	fread(&previous_num, sizeof(int), 1, *file);
	puts("\nUnique numbers:");
	printf("%d\n", previous_num);
	for (int i = 1; i < total_numbers; i++)
	{
		fread(&current_num, sizeof(int), 1, *file);
		if (current_num != previous_num)
		{
			total_unique++;
			printf("%d", current_num);
			previous_num = current_num;
		}
	}

	printf("\nTotal unique numbers: %d\n", total_unique);
}

void insert_numbers(FILE** file, char* filename, int* total_numbers)
{

}

void perform_reverse(FILE** file, char* filename, int total_numbers)
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

