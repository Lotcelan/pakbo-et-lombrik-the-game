#include "../engine/include/linked_list.h"
#include "../engine/include/test_linked_lists.h"



void test_head() {
    int value = 42;
    List* list = create_list(&value, NULL);
    assert(head(list) == &value);
    printf("test_head passed.\n");
}

void test_tail() {
    int value1 = 42, value2 = 84;
    List* list = create_list(&value1, create_list(&value2, NULL));
    List* t = tail(list);
    assert(t->value == &value2);
    assert(t->next == NULL);
    printf("test_tail passed.\n");
}

void test_length() {
    List* list = NULL;
    assert(length(list) == 0);
    int value1 = 42, value2 = 84;
    list = create_list(&value1, create_list(&value2, NULL));
    assert(length(list) == 2);
    printf("test_length passed.\n");
}

void test_create_list() {
    int value = 42;
    List* list = create_list(&value, NULL);
    assert(list->value == &value);
    assert(list->next == NULL);
    printf("test_create_list passed.\n");
}

void test_list_del_first() {
    int* value1 = malloc(sizeof(int));
    *value1 = 42;
    int value2 = 84;
    List* list = create_list(value1, create_list(&value2, NULL));
    list = list_del_first(list, free);
    assert(list->value == &value2);
    assert(list->next == NULL);
    printf("test_list_del_first passed.\n");
}

void test_append_end() {
    int value1 = 42, value2 = 84;
    List* list = create_list(&value1, NULL);
    list = append_end(&value2, list);
    assert(length(list) == 2);
    assert(get_i_element(list, 1) == &value2);
    printf("test_append_end passed.\n");
}

void test_append_first() {
    int value1 = 42, value2 = 84;
    List* list = create_list(&value1, NULL);
    list = append_first(&value2, list);
    assert(length(list) == 2);
    assert(head(list) == &value2);
    printf("test_append_first passed.\n");
}

void test_reverse() {
    int value1 = 42, value2 = 84;
    List* list = create_list(&value1, create_list(&value2, NULL));
    list = reverse(list);
    assert(length(list) == 2);
    assert(head(list) == &value2);
    assert(get_i_element(list, 1) == &value1);
    printf("test_reverse passed.\n");
}

void test_get_i_element() {
    int value1 = 42, value2 = 84;
    List* list = create_list(&value1, create_list(&value2, NULL));
    assert(get_i_element(list, 0) == &value1);
    assert(get_i_element(list, 1) == &value2);
    printf("test_get_i_element passed.\n");
}

void test_list_del_i_element() {
    int value1 = 42, value3 = 126;
    int* value2 = malloc(sizeof(int));
    *value2 = 84;
    List* list = create_list(&value1, create_list(value2, create_list(&value3, NULL)));
    list = list_del_i_element(list, 1, free);
    assert(length(list) == 2);
    assert(get_i_element(list, 1) == &value3);
    printf("test_list_del_i_element passed.\n");
}

void test_print_list() {
    int value1 = 42, value2 = 84;
    List* list = create_list(&value1, create_list(&value2, NULL));
    printf("Printing list: ");
    print_list(list);
    printf("test_print_list passed.\n");
}

void test_delete_all_non_struct() {
    int value1 = 42, value2 = 84;
    List* list = create_list(&value1, create_list(&value2, NULL));
    delete_all_non_struct(list);
    printf("test_delete_all_non_struct passed.\n");
}

void test_compare_int() {
    int value1 = 42, value2 = 84;
    assert(compare_int(&value1, &value2) < 0);
    assert(compare_int(&value2, &value1) > 0);
    assert(compare_int(&value1, &value1) == 0);
    printf("test_compare_int passed.\n");
}

void test_prefix() {
    int value1 = 42, value2 = 84, value3 = 126;
    List* list = create_list(&value1, create_list(&value2, create_list(&value3, NULL)));
    List* pref = prefix(list, 2, free);
    assert(length(pref) == 2);
    assert(get_i_element(pref, 0) == &value1);
    assert(get_i_element(pref, 1) == &value2);
    printf("test_prefix passed.\n");
}

void test_suffix() {
    int value1 = 42, value2 = 84, value3 = 126;
    List* list = create_list(&value1, create_list(&value2, create_list(&value3, NULL)));
    List* suff = suffix(list, 1, free);
    assert(length(suff) == 1);
    assert(get_i_element(suff, 0) == &value3);
    printf("test_suffix passed.\n");
}

void test_suffix_non_delete() {
    int value1 = 42, value2 = 84, value3 = 126;
    List* list = create_list(&value1, create_list(&value2, create_list(&value3, NULL)));
    List* suff = suffix_non_delete(list, 1);
    assert(length(suff) == 1);
    assert(get_i_element(suff, 0) == &value3);
    printf("test_suffix_non_delete passed.\n");
}

void test_prefix_non_delete() {
    int value1 = 42, value2 = 84, value3 = 126;
    List* list = create_list(&value1, create_list(&value2, create_list(&value3, NULL)));
    List* pref = prefix_non_delete(list, 2);
    assert(length(pref) == 2);
    assert(get_i_element(pref, 0) == &value1);
    assert(get_i_element(pref, 1) == &value2);
    printf("test_prefix_non_delete passed.\n");
}

void test_list_delete() {
    int value1 = 42, value2 = 84;
    List* list = create_list(&value1, create_list(&value2, NULL));
    list_delete(list, free);
    printf("test_list_delete passed.\n");
}

void test_merge_sort() {
    int value1 = 84, value2 = 42, value3 = 126;
    List* list = create_list(&value1, create_list(&value2, create_list(&value3, NULL)));
    list = merge_sort(list, free, compare_int);
    assert(get_i_element(list, 0) == &value2);
    assert(get_i_element(list, 1) == &value1);
    assert(get_i_element(list, 2) == &value3);
    printf("test_merge_sort passed.\n");
}

void test_create_list_cyclic() {
    int value = 42;
    List* list = create_list_cyclic(&value, NULL);
    assert(list->value == &value);
    assert(list->next == list);
    printf("test_create_list_cyclic passed.\n");
}

void test_list_cyclic_del_first() {
    int value1 = 42, value2 = 84;
    List* list = create_list_cyclic(&value1, create_list(&value2, NULL));
    list->next->next = list;
    list = list_cyclic_del_first(list, free);
    assert(list->value == &value2);
    assert(list->next == list);
    printf("test_list_cyclic_del_first passed.\n");
}

void test_length_cyclic() {
    int value1 = 42, value2 = 84;
    List* list = create_list_cyclic(&value1, create_list(&value2, NULL));
    list->next->next = list;
    assert(length_cyclic(list) == 2);
    printf("test_length_cyclic passed.\n");
}

void test_append_cyclic_end() {
    int value1 = 42, value2 = 84;
    List* list = create_list_cyclic(&value1, NULL);
    list = append_cyclic_end(&value2, list, free);
    assert(length_cyclic(list) == 2);
    assert(get_i_element(list, 1) == &value2);
    printf("test_append_cyclic_end passed.\n");
}

void test_append_cyclic_first() {
    int value1 = 42, value2 = 84;
    List* list = create_list_cyclic(&value1, NULL);
    list = append_cyclic_first(&value2, list);
    assert(length_cyclic(list) == 2);
    assert(head(list) == &value2);
    printf("test_append_cyclic_first passed.\n");
}

void test_reverse_cyclic() {
    int value1 = 42, value2 = 84;
    List* list = create_list_cyclic(&value1, create_list(&value2, NULL));
    list->next->next = list;
    list = reverse_cyclic(list, free);
    assert(length_cyclic(list) == 2);
    assert(head(list) == &value2);
    assert(get_i_element(list, 1) == &value1);
    printf("test_reverse_cyclic passed.\n");
}

void test_list_del_i_element_cyclic() {
    int value1 = 42, value2 = 84, value3 = 126;
    List* list = create_list_cyclic(&value1, create_list(&value2, create_list(&value3, NULL)));
    list->next->next->next = list;
    list = list_del_i_element(list, 1, free);
    assert(length_cyclic(list) == 2);
    assert(get_i_element(list, 1) == &value3);
    printf("test_list_del_i_element_cyclic passed.\n");
}

void test_list_cyclic_delete() {
    int value1 = 42, value2 = 84;
    List* list = create_list_cyclic(&value1, create_list(&value2, NULL));
    list->next->next = list;
    list_cyclic_delete(list, free);
    printf("test_list_cyclic_delete passed.\n");
}

void test_merge_sort_cyclic() {
    int value1 = 84, value2 = 42, value3 = 126;
    List* list = create_list_cyclic(&value1, create_list(&value2, create_list(&value3, NULL)));
    list->next->next->next = list;
    list = merge_sort_cyclic(list, free, compare_int);
    assert(get_i_element(list, 0) == &value2);
    assert(get_i_element(list, 1) == &value1);
    assert(get_i_element(list, 2) == &value3);
    printf("test_merge_sort_cyclic passed.\n");
}

void test_map_list_cyclic() {
    int value1 = 84, value2 = 42, value3 = 126;
    List* list = create_list_cyclic(&value1, create_list(&value2, create_list(&value3, NULL)));
    list->next->next->next = list;
    List* mapped = map_list_cyclic(list, increment_int, free);
    assert(*(int*)get_i_element(mapped, 0) == value1 + 1);
    assert(*(int*)get_i_element(mapped, 1) == value2 + 1);
    assert(*(int*)get_i_element(mapped, 2) == value3 + 1);
    list_cyclic_delete(mapped, free);
    printf("test_map_list_cyclic passed.\n");
}

void test_copy_list() {
    int value1 = 42, value2 = 84;
    List* list = create_list(&value1, create_list(&value2, NULL));
    List* copy = copy_list(list, copy_int);
    assert(length(copy) == length(list));
    assert(*(int*)head(copy) == value1);
    assert(*(int*)get_i_element(copy, 1) == value2);
    list_delete(copy, free);
    printf("test_copy_list passed.\n");
}

void test_copy_cyclic_list() {
    int value1 = 42, value2 = 84;
    List* list = create_list_cyclic(&value1, create_list(&value2, NULL));
    list->next->next = list;
    List* copy = copy_cyclic_list(list, copy_int);
    assert(length_cyclic(copy) == length_cyclic(list));
    assert(*(int*)head(copy) == value1);
    assert(*(int*)get_i_element(copy, 1) == value2);
    list_cyclic_delete(copy, free);
    printf("test_copy_cyclic_list passed.\n");
}


// Fonctions d'aide pour les tests
void* increment_int(void* a) {
    (*(int*)a) += 1;
    return a;
}

void* copy_int(void* a) {
    int* new_val = malloc(sizeof(int));
    *new_val = *(int*)a;
    return new_val;
}