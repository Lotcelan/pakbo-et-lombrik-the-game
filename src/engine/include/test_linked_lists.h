#ifndef TEST_BINARY_HEAP_H
#define TEST_BINARY_HEAP_H

#include "linked_list.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>

void test_head();
void test_tail();
void test_length();
void test_create_list();
void test_list_del_first();
void test_append_end();
void test_append_first();
void test_reverse();
void test_get_i_element();
void test_list_del_i_element();
void test_print_list();
void test_delete_all_non_struct();
void test_compare_int();
void test_prefix();
void test_suffix();
void test_suffix_non_delete();
void test_prefix_non_delete();
void test_list_delete();
void test_merge_sort();
void test_create_list_cyclic();
void test_list_cyclic_del_first();
void test_length_cyclic();
void test_append_cyclic_end();
void test_append_cyclic_first();
void test_reverse_cyclic();
void test_list_del_i_element_cyclic();
void test_list_cyclic_delete();
void test_merge_sort_cyclic();
void test_map_list_cyclic();
void test_copy_list();
void test_copy_cyclic_list();

// Fonctions d'aide pour les tests
void* increment_int(void* a);
void* copy_int(void* a);

#endif