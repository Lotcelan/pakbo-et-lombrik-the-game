#include "../engine/include/binary_heap.h"
#include "../engine/include/test_binary_heap.h"

void test_binary_heap_create() {
    printf("Testing binary_heap_create()\n");
    // Test case 1: Create a binary heap with capacity 10
    binary_heap* bh1 = binary_heap_create(10, binary_heap_basic_entry_compare);
    assert(bh1 != NULL);
    assert(bh1->size == 0);
    assert(bh1->capacity == 10);
    binary_heap_free(bh1);
    
    // Test case 2: Create a binary heap with capacity 0
    binary_heap* bh2 = binary_heap_create(0, binary_heap_basic_entry_compare);
    assert(bh2 != NULL);
    assert(bh2->size == 0);
    assert(bh2->capacity == 0);
    binary_heap_free(bh2);
}

// void test_binary_heap_insert() {
//     printf("Testing binary_heap_insert()\n");
//     // Test case 1: Insert a value into an empty binary heap
//     binary_heap* bh1 = binary_heap_create(10, binary_heap_basic_entry_compare);
//     binary_heap_insert(bh1, create_binary_heap_basic_entry("value1", 1.0));
//     assert(bh1->size == 1);
//     assert(strcmp((char*)(bh1->array[0]->value), "value1") == 0);
//     binary_heap_free(bh1);
    
//     // Test case 2: Insert multiple values into a binary heap
//     binary_heap* bh2 = binary_heap_create(10, binary_heap_basic_entry_compare);
//     binary_heap_insert(bh2, create_binary_heap_basic_entry("value1", 1.0));
//     binary_heap_insert(bh2, create_binary_heap_basic_entry("value2", 2.0));
//     binary_heap_insert(bh2, create_binary_heap_basic_entry("value3", 0.5));
//     assert(bh2->size == 3);
//     assert(bh2->array[0]->value == "value3");
//     assert(bh2->array[1]->value == "value1");
//     assert(bh2->array[2]->value == "value2");
//     binary_heap_free(bh2);
// }

// void test_binary_heap_modify() {
//     printf("Testing binary_heap_modify()\n");
//     // Test case 1: Modify a value in the binary heap
//     binary_heap* bh1 = binary_heap_create(10, binary_heap_basic_entry_compare);
//     binary_heap_insert(bh1, create_binary_heap_basic_entry("value1", 1.0));
//     binary_heap_insert(bh1, create_binary_heap_basic_entry("value2", 2.0));
//     binary_heap_modify(bh1, "value1", create_binary_heap_basic_entry("new_value", 0.5), cmp);
//     assert(bh1->size == 2);
//     assert(bh1->array[0]->value == "new_value");
//     assert(bh1->array[1]->value == "value2");
//     binary_heap_free(bh1);
    
//     // Test case 2: Modify a value that is not present in the binary heap
//     binary_heap* bh2 = binary_heap_create(10, binary_heap_basic_entry_compare);
//     binary_heap_insert(bh2, create_binary_heap_basic_entry("value1", 1.0));
//     binary_heap_insert(bh2, create_binary_heap_basic_entry("value2", 2.0));
//     binary_heap_modify(bh2, "value3", create_binary_heap_basic_entry("new_value", 0.5), cmp);
//     assert(bh2->size == 2);
//     assert(bh2->array[0]->value == "value1");
//     assert(bh2->array[1]->value == "value2");
//     binary_heap_free(bh2);
// }

// void test_is_present_in_binary_heap() {
//     printf("Testing is_present_in_binary_heap()\n");
//     // Test case 1: Check if a value is present in the binary heap
//     binary_heap* bh1 = binary_heap_create(10, binary_heap_basic_entry_compare);
//     binary_heap_insert(bh1, create_binary_heap_basic_entry("value1", 1.0));
//     binary_heap_insert(bh1, create_binary_heap_basic_entry("value2", 2.0));
//     assert(is_present_in_binary_heap(bh1, "value1", cmp) == true);
//     assert(is_present_in_binary_heap(bh1, "value2", cmp) == true);
//     assert(is_present_in_binary_heap(bh1, "value3", cmp) == false);
//     binary_heap_free(bh1);
    
//     // Test case 2: Check if a value is present in an empty binary heap
//     binary_heap* bh2 = binary_heap_create(10, binary_heap_basic_entry_compare);
//     assert(is_present_in_binary_heap(bh2, "value1", cmp) == false);
//     binary_heap_free(bh2);
// }

// void test_display_binary_heap() {
//     printf("Testing display_binary_heap()\n");
//     // Test case 1: Display an empty binary heap
//     binary_heap* bh1 = binary_heap_create(10, binary_heap_basic_entry_compare);
//     display_binary_heap(bh1, display);
//     binary_heap_free(bh1);
    
//     // Test case 2: Display a non-empty binary heap
//     binary_heap* bh2 = binary_heap_create(10, binary_heap_basic_entry_compare);
//     binary_heap_insert(bh2, create_binary_heap_basic_entry("value1", 1.0));
//     binary_heap_insert(bh2, create_binary_heap_basic_entry("value2", 2.0));
//     display_binary_heap(bh2, display);
//     binary_heap_free(bh2);
// }

// void test_binary_heap_extract() {
//     printf("Testing binary_heap_extract()\n");
//     // Test case 1: Extract the minimum value from a binary heap
//     binary_heap* bh1 = binary_heap_create(10, binary_heap_basic_entry_compare);
//     binary_heap_insert(bh1, create_binary_heap_basic_entry("value1", 1.0));
//     binary_heap_insert(bh1, create_binary_heap_basic_entry("value2", 2.0));
//     void* extracted_value = binary_heap_extract(bh1);
//     assert(extracted_value == "value1");
//     assert(bh1->size == 1);
//     assert(bh1->array[0]->value == "value2");
//     binary_heap_free(bh1);
    
//     // Test case 2: Extract the minimum value from an empty binary heap
//     binary_heap* bh2 = binary_heap_create(10, binary_heap_basic_entry_compare);
//     void* extracted_value2 = binary_heap_extract(bh2);
//     assert(extracted_value2 == NULL);
//     assert(bh2->size == 0);
//     binary_heap_free(bh2);
// }

// void test_is_binary_heap_empty() {
//     printf("Testing is_binary_heap_empty()\n");
//     // Test case 1: Check if an empty binary heap is empty
//     binary_heap* bh1 = binary_heap_create(10, binary_heap_basic_entry_compare);
//     assert(is_binary_heap_empty(bh1) == true);
//     binary_heap_free(bh1);
    
//     // Test case 2: Check if a non-empty binary heap is empty
//     binary_heap* bh2 = binary_heap_create(10, binary_heap_basic_entry_compare);
//     binary_heap_insert(bh2, create_binary_heap_basic_entry("value1", 1.0));
//     assert(is_binary_heap_empty(bh2) == false);
//     binary_heap_free(bh2);
// }

// void test_create_binary_heap_basic_entry() {
//     printf("Testing create_binary_heap_basic_entry()\n");
//     // Test case 1: Create a binary heap basic entry with a value and priority
//     binary_heap_basic_entry* entry1 = create_binary_heap_basic_entry("value1", 1.0);
//     assert(entry1 != NULL);
//     assert(entry1->value == "value1");
//     assert(entry1->priority == 1.0);
//     free(entry1);
    
//     // Test case 2: Create a binary heap basic entry with a NULL value and priority
//     binary_heap_basic_entry* entry2 = create_binary_heap_basic_entry(NULL, 0.0);
//     assert(entry2 != NULL);
//     assert(entry2->value == NULL);
//     assert(entry2->priority == 0.0);
//     free(entry2);
// }
