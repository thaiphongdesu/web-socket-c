#include <stdbool.h>
#include "singly.h"

#define file_name "setting_file.txt"
#define READ "r"
#define MAX_S 245

char* remove_comment(char *buffer);
int separate_line(char *source, char *key);
void initialize_from_file(int *service, int* protocol, int* port, int *backlog);
bool section_exist(const char *buffer, const char *section_name);

struct Sections {
    char path_of_file[ARRAY_SIZE];
    char parent_path[ARRAY_SIZE];
    //char section_name[ARRAY_SIZE];
    struct Singly *list;
};


struct Sections *read_section(char section_name[ARRAY_SIZE]);
void parsing_to_struct(struct Sections*, FILE *fptr);
struct Sections *parse_sections();
struct Singly *find_section(const char *buffer, struct Sections *sections);
bool str_cmp_case_insensitive(const char *str1,const char *str2);
void initialize_from_parsed_section(struct Singly *section, int *service, int* protocol, int* port, int *backlog);