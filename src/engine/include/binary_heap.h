#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <stdlib.h>
#include <stdio.h>

typedef struct binary_heap {
    void** array;
    int (*compare)(void*, void*); // Returns a value > 0 if the first argument is greater than the second, 0 if they are equal, and < 0 if the first argument is less than the second.
    int size;
    int capacity;
} binary_heap;

binary_heap* binary_heap_create(int capacity, int (*compare)(void*, void*));
void binary_heap_insert(binary_heap *bh, void* value);
void display_binary_heap(binary_heap* bh, void (*display)(void*));
void* binary_heap_extract(binary_heap* bh);
void min_heapify(binary_heap* bh, int i);
void binary_heap_free(binary_heap* bh);

#endif