#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct List {
    void* value;
    struct List* next;
} List;

List* init_linked_list(void* value);
void append(void* value, List** pList);
void map(void* (*f)(void*), List* list);

int length(List *list);

List *create_list(void *value, List *next);
List *list_del_first( List *l, void delete(List*);
List *append_end(void *value, List *list);
List *append_first(void *value, List *list);
List *reverse(List *list);
List *list_del_i_element(List *l, int ind, void delete(List*));
void print_list(List *list);
void delete_all_non_struct(List *l);
List *merge(List *list1, List *list2, void delete(List*), int comparaison(void*, void*));
int compare_int(void *a, void *b);
List *prefix(List *list, int n, void delete(List*));
List *suffix(List *list, int n, void delete(List*));
List *suffix_non_delete(List *list, int n);
List *prefix_non_delete(List *list, int n);
void list_delete(List *list, void delete(List*));
List *merge_sort(List *list, void delete(List*), int comparaison(void*, void*));
int compare_str(void *a, void *b);
    
#endif
