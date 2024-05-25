#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
// oups j'ai pas pensé à tout ce qui était free, on verra ca plus tard

typedef struct binary_heap_basic_entry {
    void* value;
    float priority; // Je mets à disposition le cas le plus classique d'utilisation, soit une priorité flottante
} binary_heap_basic_entry;

typedef struct binary_heap {
    void** array;
    int (*compare)(void*, void*); // IN TERMES OF COMPARISON TO PLACE IN THE TREE Returns a value > 0 if the first argument is greater than the second, 0 if they are equal, and < 0 if the first argument is less than the second.
    int size;
    int capacity;
} binary_heap;

binary_heap* binary_heap_create(int capacity, int (*compare)(void*, void*));
void binary_heap_insert(binary_heap *bh, void* value);
void display_binary_heap(binary_heap* bh, void (*display)(void*));
void* binary_heap_extract(binary_heap* bh);
void min_heapify(binary_heap* bh, int i);
void binary_heap_free(binary_heap* bh);
int binary_heap_basic_entry_compare(void* e1, void* e2);
binary_heap_basic_entry* create_binary_heap_basic_entry(void* value, float priority);
bool is_binary_heap_empty(binary_heap* bh);
bool is_present_in_binary_heap(binary_heap* bh, void* value, bool (*cmp)(void*, void*)); // on n'utilise pas le même compare que dans la structure car là on compare les values par les priorités
void binary_heap_modify(binary_heap* bh, void* to_modify, void* new_value, bool (*cmp)(void* v1, void* v2)); // même principe
void binary_heap_basic_entry_free(void* bhe);
void binary_heap_free(binary_heap* bh);
#endif
