#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdlib.h>
#include <stdio.h>

typedef struct List {
    void* value;
    struct List* next;
} List;

List* init_linked_list(void* value);
void append(void* value, List** pList);
void map(void* (*f)(void*), List* list);

#endif