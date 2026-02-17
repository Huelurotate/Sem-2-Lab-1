#define EXTENSION_LEN 4
#define WRITE_CHOICE 1
#define APPEND_CHOICE 0
#define RAND_MIN -100
#define RAND_MAX 100
#define RAND_LEN_MIN 2
#define RAND_LEN_MAX 15

void create_filename(char** filename_var, char* user_input);
void check_filename(char** filename);
void filename_input(char** str, int* length);

void menu(FILE** file, char* filename);
void print_menu();
void option_choice(int* choice);

void input(FILE** file, char* filename, int* total_numbers);
void manual_input(FILE** file, char* filename, int* total_numbers, int user_input_choice);
void random_input(FILE** file, char* filename, int* total_numbers, int user_input_choice);

void input_choice(int* choice);
void random_choice(int* choice);
void choice_loop(int* choice_var);
void find_last_element(FILE** file, int* last_element_var);

void output(FILE** file, char* filename, int total_numbers);

void count_unique(FILE**, char* filename, int total_numbers);

void insert_numbers(FILE** file, char* filename, int* total_numbers);

void perform_reverse(FILE** file, char* filename, int total_numbers);

void file_opening_check(FILE* file);
void check_arr_alloc(int* arr);