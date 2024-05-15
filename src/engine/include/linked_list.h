#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct List {
    void* value;
    struct List* next;
} List;


void* head(List *list);
List* tail(List *list);

// Final primitives
int length(List *list);

List *create_list(void *value, List *next);
List *list_del_first( List *l, void delete(void*));
List *append_end(void *value, List *list);
List *append_first(void *value, List *list);
List *reverse(List *list);
void* get_i_element(List *list, int i);
List *list_del_i_element(List *l, int ind, void delete(void*));
void print_list(List *list);
void delete_all_non_struct(List *l);
List* delete_compare(List* l, void* value, int compare(void*, void*), void delete(void*));
List *merge(List *list1, List *list2, void delete(void*), int comparaison(void*, void*));
int compare_int(void *a, void *b);
List *prefix(List *list, int n, void delete(void*));
List *suffix(List *list, int n, void delete(void*));
List *suffix_non_delete(List *list, int n);
List *prefix_non_delete(List *list, int n);
void list_delete(List *list, void delete(void*));
List *merge_sort(List *list, void delete(void*), int comparaison(void*, void*));
int compare_str(void *a, void *b);
List *create_list_cyclic(void *value, List *next) ;

void print_list_cyclic(List *list) ;

List *list_cyclic_del_first( List *l, void delete(void*) ) ;

int length_cyclic(List *list) ;

List *append_cyclic_end(void *value, List *list, void delete(void*)) ;

List *append_cyclic_first(void *value, List *list) ;

List *reverse_cyclic(List *list, void delete(void*)) ;

List *list_del_i_element(List *l, int ind, void delete(void*)) ;

List *merge_cyclic(List *list1, List *list2, void delete(void*), int comparaison(void*, void*)) ;

List *suffix_cyclic_non_delete(List *list, int n, List *first) ;

List *prefix_cyclic_non_delete(List *list, int n) ;

void list_cyclic_delete(List *list, void delete(void*)) ;

List *merge_sort_cyclic(List *list, void delete(void*), int comparaison(void*, void*)) ;

List *map_list_cyclic(List *list, void *f(void *a), void delete(void*)) ;

List* copy_list(List* to_copy, void* (*copy_value)(void*));
List* copy_cyclic_list(List* to_copy, void* (*copy_value)(void*));
#endif
