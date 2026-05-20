#include "singly.h"
#include <stdlib.h>
#include <stdio.h>

struct Node *alloc_node(const char *data) {
    struct Node *node = malloc(sizeof(struct Node));
    if(!node) return NULL;
    snprintf(node->data, 100, "%s", data);
    node->next = NULL;
    return node;
}

struct Singly *alloc_list(const char *data) {
    struct Singly *list = calloc(1, sizeof(struct Singly));
    if(!list) return NULL;
    snprintf(list->list_name, 100, "%s", data);
    return list;
}

void de_allocate(struct Singly *list) {
    struct Node *tmp, *node;
    if(list->size > 0) {
        node = list->begin;
        while(list->size--) {
            tmp = node;
            node = node->next;
            free(tmp);
        }
    }
}

void de_allocate_list(struct Singly *list) {
    struct Singly *temp = list, *holder = list;
    while(holder) {
        temp = temp->next;
        de_allocate(holder);
        free(holder);
        holder = temp;
    }
}

void push_back(struct Singly *list, struct Node *node) {
    if(!list->size) {
        list->begin = node;
        list->size = 1;
    } else {
        struct Node *tmp = list->begin;
        while(tmp->next) {
            tmp = tmp->next;
        }
        tmp->next = node;
        list->size += 1;
    }
}

void push_back_list(struct Singly *list, struct Singly *list_back) {
    struct Singly *temp = list;
    while(temp->next) {
        temp = temp->next;
    }
    temp->next = list_back;
    list_back->next = NULL;
}

struct Node *next(struct Node *node) {
    if(node->next) return node->next;
    return NULL;
}

char *get_section_name(struct Singly *singly) {
    return singly->list_name;
}