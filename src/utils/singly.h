#ifndef SINGLY_H
#define SINGLY_H

#define ARRAY_SIZE 256
struct Node {
    char data[ARRAY_SIZE];
    struct Node *next;
};

struct Singly {
    char list_name[ARRAY_SIZE];
    struct Node *begin;
    struct Singly *next;
    unsigned int size;
};

struct Node *alloc_node(const char *data);
struct Singly *alloc_list(const char *data);
void de_allocate(struct Singly *list);
void push_back(struct Singly *list, struct Node *node);
struct Node *next(struct Node *node);
char *get_section_name(struct Singly *);
void push_back_list(struct Singly *list, struct Singly *list_back);
void de_allocate_list(struct Singly *list);

#endif