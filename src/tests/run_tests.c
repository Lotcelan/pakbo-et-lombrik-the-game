#include "../engine/include/run_tests.h"

int main() {
    printf("Testing the Binary heap structure\n");
    // test_binary_heap_create();
    // test_binary_heap_insert();
    // test_binary_heap_modify();
    // test_is_present_in_binary_heap();
    // test_display_binary_heap();
    // test_binary_heap_extract();
    // test_is_binary_heap_empty();
    // test_create_binary_heap_basic_entry();
    printf("Testing the Linked list structure\n");

     test_head();
    test_tail();
    test_length();
    test_create_list();
    test_list_del_first();
    test_append_end();
    test_append_first();
    test_reverse();
    test_get_i_element();
    test_list_del_i_element();
    test_print_list();
    test_delete_all_non_struct();
    test_compare_int();
    test_prefix();
    test_suffix();
    test_suffix_non_delete();
    test_prefix_non_delete();
    test_list_delete();
    test_merge_sort();
    test_create_list_cyclic();
    test_list_cyclic_del_first();
    test_length_cyclic();
    test_append_cyclic_end();
    test_append_cyclic_first();
    test_reverse_cyclic();
    test_list_del_i_element_cyclic();
    test_list_cyclic_delete();
    test_merge_sort_cyclic();
    test_map_list_cyclic();
    test_copy_list();
    test_copy_cyclic_list();
    printf("All tests passed.\n");
}