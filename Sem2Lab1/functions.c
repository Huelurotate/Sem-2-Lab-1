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
		check_char_alloc(*filename_var);
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
		check_char_alloc(*str);
		(*str)[*length - 1] = c;
	}

	(*str)[*length] = '\0';
}

void check_char_alloc(char* memory_block)
{
	if (memory_block == NULL)
	{
		puts("Memory allocation error.");
		exit(1);
	}
}

void menu(char* filename)
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
			input(filename, &total_numbers);
			break;
		case 2:
			if (total_numbers != 0)
				output(filename, total_numbers);
			else
				puts("\nThe file is empty.");
			break;
		case 3:
			if (total_numbers != 0)
				count_unique(filename, total_numbers);
			else
				puts("\nThe file is empty.");
			break;
		case 4:
			if (total_numbers != 0)
				insert_numbers(filename, &total_numbers);
			else
				puts("\nThe file is empty.");
			break;
		case 5:
			if (total_numbers != 0)
				perform_reverse(filename, total_numbers);
			else
				puts("\nThe file is empty.");
			break;
		case 6:
			is_running = 0;
			break;
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
	while (scanf_s("%d", choice) != 1 || *choice < 1 || *choice > 6)
	{
		puts("Invalid Input.");
		rewind(stdin);
	}
}

void input(char* filename, int* total_numbers)
{
	int user_input_choice = WRITE_CHOICE;
	int user_random_choice;

	if (*total_numbers != 0)
		input_choice(&user_input_choice);

	random_choice(&user_random_choice);

	if (user_random_choice)
		random_input(filename, total_numbers, user_input_choice);
	else
		manual_input(filename, total_numbers, user_input_choice);
}

void manual_input(char* filename, int* total_numbers, int user_input_choice)
{
	FILE* bin_file;
	int last_element = 0;
	int has_last_element = 0;
	
	select_open_mode(&bin_file, filename, total_numbers, \
					 user_input_choice, &last_element, &has_last_element);

	file_opening_check(bin_file);

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
			(has_last_element && num > last_element))
		{
			if (has_last_element)
				printf("Invalid Input. Enter a number less or equal to %d\n", last_element);
			else
				printf("Invalid Input.\n");
				
			rewind(stdin);
		}

		last_element = num;
		has_last_element = 1;

		fwrite(&num, sizeof(int), 1, bin_file);
		(*total_numbers)++;
	}

	fclose(bin_file);
}

void random_input(char* filename, int* total_numbers, int user_input_choice)
{
	FILE* bin_file;
	int max_num = RAND_MAX;
	int has_last_element = 0;

	select_open_mode(&bin_file, filename, total_numbers, \
					 user_input_choice, &max_num, &has_last_element);

	file_opening_check(bin_file);

	if (max_num < RAND_MIN)
	{
		puts("\nThe last element of the file exceeds the bottom random limit.");
		return;
	}

	int random_length = (rand() % (RAND_LEN_MAX - RAND_LEN_MIN + 1)) + RAND_LEN_MIN;
	int random_num;

	for (int i = 0; i < random_length; i++)
	{
		random_num = (rand() % (max_num - RAND_MIN + 1)) + RAND_MIN;
		fwrite(&random_num, sizeof(int), 1, bin_file);
		max_num = random_num;
	}

	*total_numbers += random_length;

	fclose(bin_file);

	puts("\nRandom numbers have been added to the file.");
}

void input_choice(int* choice)
{
	printf("\nWrite or Append to the file?(1 - Write, 0 - Append): ");
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

void select_open_mode(FILE** file, 
					  char* filename_var, 
					  int* total_numbers_value,
					  int user_input_var, 
					  int* last_element_var, 
					  int* has_last_element)
{
	if ((*total_numbers_value != 0 && user_input_var == WRITE_CHOICE) || *total_numbers_value == 0)
	{
		
		*file = fopen(filename_var, "wb");
		file_opening_check(*file);
		*total_numbers_value = 0;
		*has_last_element = 0;
	}
	else if (*total_numbers_value != 0 && user_input_var == APPEND_CHOICE)
	{
		*file = fopen(filename_var, "ab+");
		file_opening_check(*file);
		find_last_element(file, last_element_var);
		*has_last_element = 1;
	}
}

void find_last_element(FILE** file, int* last_element_var)
{
	fseek(*file, (0 - sizeof(int)), SEEK_END);
	fread(last_element_var, sizeof(int), 1, *file);
	fseek(*file, 0, SEEK_END);
}

void output(char* filename, int total_numbers)
{
	FILE* bin_file = fopen(filename, "rb");
	file_opening_check(bin_file);

	int num;

	puts("Contents of the file are:");
	for (int i = 0; i < total_numbers; i++)
	{
		fread(&num, sizeof(int), 1, bin_file);
		printf("%d\n", num);
	}

	fclose(bin_file);
}

void count_unique(char* filename, int total_numbers)
{
	FILE* bin_file = fopen(filename, "rb");
	file_opening_check(bin_file);

	int previous_num, current_num, total_unique = 1;

	fread(&previous_num, sizeof(int), 1, bin_file);
	puts("\nUnique numbers:");
	printf("%d\n", previous_num);
	for (int i = 1; i < total_numbers; i++)
	{
		fread(&current_num, sizeof(int), 1, bin_file);
		if (current_num != previous_num)
		{
			total_unique++;
			printf("%d\n", current_num);
			previous_num = current_num;
		}
	}

	printf("\nTotal unique numbers: %d\n", total_unique);

	fclose(bin_file);
}

void insert_numbers(char* filename, int* total_numbers)
{
	int user_random_choice;
	printf("\nInsert random numbers into the file?(1 - Yes, 0 - No): ");
	choice_loop(&user_random_choice);

	if (user_random_choice)
		random_insert(filename, total_numbers);
	else
		manual_insert(filename, total_numbers);

	bubble_sort(filename, *total_numbers);
	puts("Numbers have been inserted into the file.");
}

void manual_insert(char* filename, int* total_numbers)
{
	FILE* bin_file = fopen(filename, "ab");
	file_opening_check(bin_file);

	while (1)
	{
		getchar();

		puts("\nEnter a number to insert into the file:");

		char char_input = getchar();

		if (char_input == '\n')
			break;

		ungetc(char_input, stdin);

		int num;
		while (scanf_s("%d", &num) != 1)
		{
			printf("Invalid Input.\n");
			rewind(stdin);
		}

		fwrite(&num, sizeof(int), 1, bin_file);
		(*total_numbers)++;
	}

	fclose(bin_file);
}

void random_insert(char* filename, int* total_numbers)
{
	FILE* bin_file = fopen(filename, "ab");
	file_opening_check(bin_file);

	int random_length = (rand() % (RAND_LEN_MAX - RAND_LEN_MIN + 1)) + RAND_LEN_MIN;
	int random_num;

	for (int i = 0; i < random_length; i++)
	{
		random_num = (rand() % (RAND_MAX - RAND_MIN + 1)) + RAND_MIN;
		fwrite(&random_num, sizeof(int), 1, bin_file);
	}

	*total_numbers += random_length;

	fclose(bin_file);

	puts("\nRandom numbers have been inserted into the file.");
}

void bubble_sort(char* filename, int total_numbers)
{
	FILE* bin_file = fopen(filename, "rb+");
	file_opening_check(bin_file);

	int x1 = 0, x2 = 0;
	int swapped;

	for (int i = 0; i < total_numbers - 1; i++)
	{
		swapped = 0;
		for (int j = 0; j < total_numbers - i - 1; j++)
		{
			fread(&x1, sizeof(int), 1, bin_file);
			fread(&x2, sizeof(int), 1, bin_file);
			if (x2 > x1)
			{
				fseek(bin_file, -2 * sizeof(int), SEEK_CUR);
				fwrite(&x2, sizeof(int), 1, bin_file);
				fwrite(&x1, sizeof(int), 1, bin_file);
				fseek(bin_file, -1 * sizeof(int), SEEK_CUR);

				swapped = 1;
			}
			else fseek(bin_file, -1 * sizeof(int), SEEK_CUR);
		}
		if (swapped == 0)
			break;

		rewind(bin_file);
	}

	fclose(bin_file);
}

void perform_reverse(char* filename, int total_numbers)
{
	FILE* bin_file = fopen(filename, "rb+");


}

void file_opening_check(FILE* file)
{
	if (file == NULL)
	{
		puts("Failed to open the file.");
		exit(1);
	}
}
