#define EXTENSION_LEN 4
#define WRITE_CHOICE 1
#define APPEND_CHOICE 0
#define RAND_MIN -9999
#define RAND_MAX 9999
#define RAND_LEN_MIN 2
#define RAND_LEN_MAX 50

void check_filename(char** filename);

void menu(FILE** file, char* filename);
void print_menu();
void option_choice(int* choice);

void input(FILE** file, char* filename, int* total_numbers, int* user_random_choice);
void manual_input(FILE** file, char* filename, int* total_numbers, int user_input_choice);
void random_input(FILE** file, char* filename, int* total_numbers, int user_input_choice);

void input_choice(int* choice);
void random_choice(int* choice);
void choice_loop(int** choice_var);

void output(FILE** file, char* filename, int* total_numbers);

void add_numbers(FILE* file);

void perform_reverse(FILE* file);

void str_input(char** str);
