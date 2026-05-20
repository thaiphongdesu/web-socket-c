#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"

// apply for "//" format
char* remove_comment_unnecessary(char *buffer) {
    char *result = calloc(100, sizeof(char));
    int i = 0, b_len = strlen(buffer);
    // trim spaces leading
    while(buffer[0] == ' ' || buffer[0] == '\n' || buffer[0] == '\r') {
        buffer++;
    }

    while(buffer[i] != '/') {
        i++;
        if(i == b_len) break;
    }
    if(buffer[strlen(buffer)] == 10){ //remove \n \r lf for clean data 
        
        i = strlen(buffer) - 1;
    }
    snprintf(result, i, "%s", buffer);

    // trim \n lf in the end of string
    i = 0;
    while(i <= strlen(result)) { 
        if(result[i] == 10) {
            result[i] = '\0';
            break;
        }
        i++;
    }

    return result;
}

int separate_line(char *source, char *param_1) {
    int i = 0, s_len = strlen(source);
    char *number = source;
    while(source[i] != '=') {
        number++;
        i++;
        if(i == s_len) break;
    }
    number++;

    snprintf(param_1, i, "%s", source);

    return atoi(number);
}

bool str_cmp_case_insensitive(const char *str1, const char *str2) {
    if(strlen(str1) != strlen(str2)) return false;
    unsigned int i = 0;
    while(str1[i] != '\0') {
        char c = str1[i];
        if(c > 64 && c < 91) { // uppercase
            if(!(c + 32 == str2[i] || c == str2[i])) {
                return false;
            }
        } else if(c > 96 && c < 122) {  // lowercase
            if(!(c - 32 == str2[i] || c == str2[i])) {
                return false;
            }
        } else if(c != str2[i]) return false;
        i++;
    }
    return true;
}

int copy_section(const char *buffer, char * destination) {
    //char *result = calloc(100, sizeof(char));
    while(buffer[0] == '[' || buffer[0] == ' ') {
        buffer++; // trim [ && ' '
    }
    unsigned int i = 0, b_len = strlen(buffer);
    while(buffer[i] != ']') {
        i++;
        if(i == b_len) break; // avoid undefined behavior
    }
    snprintf(destination, i + 1, "%s", buffer);
    return strlen(destination);
}

int copy_item(const char *buffer, char *destination) {
    //char *result = calloc(100, sizeof(char));
    unsigned int i = 0, b_len = strlen(buffer);
    while(buffer[i] != '\0') {
        i++;
        if(i == b_len) break; // avoid undefined behavior
    }
    snprintf(destination, i, "%s", buffer);
    return strlen(destination);
}

void initialize_from_file(int *service, int* protocol, int* port, int *backlog) {
    FILE *fptr;
    char buffer[100] = {0};
    fptr = fopen(file_name, READ);

    if(fptr == NULL) {
        perror("Could not open setting file.\n");
        exit(1);
    }

    while(fgets(buffer, 100, fptr)) { 
        char * s = remove_comment_unnecessary(buffer);
        // printf("return string of remove comment: %s \n", s);
        if(strlen(s) > 0) {
            char *param = calloc(100, sizeof(char));
            int temp = 0;
            temp = separate_line(s, param);
            // printf("initialize_from_file debug 1: param: %s | temp: %d", param, temp);
            if(strcmp(param, "service") == 0) {
                *service = temp;
            } else if(strcmp(param, "protocol") == 0) {
                *protocol = temp;
            } else if(strcmp(param, "port") == 0) {
                *port = temp;
            } else if(strcmp(param, "backlog") == 0) {
                *backlog = temp;
            }
            free(param);
        }
        free(s);
    }

    fclose(fptr);
}

void initialize_from_parsed_section(struct Singly *section, int *service, int* protocol, int* port, int *backlog) {
    struct Node *item = section->begin;
    while(item) {
        char *param = calloc(100, sizeof(char));
        int temp = 0;
        temp = separate_line(item->data, param);
        if(strcmp(param, "service") == 0) {
            *service = temp;
        } else if(strcmp(param, "protocol") == 0) {
            *protocol = temp;
        } else if(strcmp(param, "port") == 0) {
            *port = temp;
        } else if(strcmp(param, "backlog") == 0) {
            *backlog = temp;
        }
        free(param);
        item = item->next;
    }
}

//     struct Section {
//     char path_of_file[array_size];
//     char parent_path[array_size];
//     struct Singly *list_item;
//      };
struct Sections *parse_sections() {
    char buffer[100] = {0};
    struct Sections *sections = calloc(1, sizeof(struct Sections));
    FILE *fptr;
    fptr = fopen(file_name, READ);
    if(!fptr) {
        perror("Can not open file.");
        printf("File name: %s\n", file_name);
        exit(1);
    }
    // printf("read_section debug 1\n");
    while(fgets(buffer, 100, fptr)) {
        char * s = remove_comment_unnecessary(buffer);
        if(strlen(s) <= 0) {
            free(s);
            continue;
        }
        
        // handle for sections
        if(s[0] == '[') { // section is found
            struct Singly *list = calloc(1, sizeof(struct Singly));
            if(sections->list == NULL) {
                sections->list = list;
            } else {
                push_back_list(sections->list, list);
            }
            if(copy_section(s, list->list_name) == 0) {
                printf("Failed to copy section name\n");
            }
        } else { // handle for items in a section
            struct Singly *temp = sections->list;
            while(temp->next) {
                temp = temp->next;
            }
            struct Node *item = alloc_node(s);
            push_back(temp, item);
        }
        free(s);
        memset(buffer, 0, 100);
    }

    return sections;
}

bool section_exist(const char *buffer, const char *section_name) {
    if(buffer[0] == '[') {
        char *temp = (char*)buffer;
        temp++;
        int i = 2;

        while(buffer[i] != ']') {
            i++;
            if(i == MAX_S) return false;
        }

        temp[i - 1] = '\0';
        if(strcmp(section_name, temp) == 0) {
            return true;
        }
    }
    return false;
}

struct Singly *find_section(const char *buffer, struct Sections *sections) {
    struct Singly *result = NULL, *temp = sections->list;
    while(temp) {
        if(str_cmp_case_insensitive(temp->list_name, buffer)) { // section is found in object
            result = temp;
            break;
        }
        temp = temp->next;
    }
    return result;
}
