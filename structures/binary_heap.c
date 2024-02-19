#include "binary_heap.h"

binary_heap* binary_heap_create(int capacity, int (*compare)(void*, void*)) {
    binary_heap* bh = malloc(sizeof(binary_heap));
    bh->array = malloc(capacity * sizeof(void*));
    
    bh->compare = compare;
    bh->size = 0;
    bh->capacity = capacity;
    
    return bh;
}

void binary_heap_insert(binary_heap *bh, void* value) {
    if (bh->size == bh->capacity) {
        // Resize the array
        bh->capacity = bh->capacity * 2 + 1;
        bh->array = realloc(bh->array, bh->capacity * sizeof(void*));
    }
    
    bh->size++;
    int i = bh->size - 1;
    bh->array[i] = value;
    
    while (i != 0 && bh->compare(bh->array[(i - 1) / 2], bh->array[i]) > 0) {
        void* temp = bh->array[i];
        bh->array[i] = bh->array[(i - 1) / 2];
        bh->array[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}   

void display_binary_heap(binary_heap* bh, void (*display)(void*)) {
    for (int i = 0; i < bh->size; i++) {
        display(bh->array[i]);
    }
    printf("\n");
}

void* binary_heap_extract(binary_heap* bh) {
    if (bh->size == 0) {
        return NULL;
    }
    
    if (bh->size == 1) {
        bh->size--;
        return bh->array[0];
    }
    
    void* root = bh->array[0];
    bh->array[0] = bh->array[bh->size - 1];
    bh->size--;
    min_heapify(bh, 0);
    
    return root;
}

void min_heapify(binary_heap* bh, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;
    
    if (left < bh->size && bh->compare(bh->array[left], bh->array[smallest]) < 0) {
        smallest = left;
    }
    
    if (right < bh->size && bh->compare(bh->array[right], bh->array[smallest]) < 0) {
        smallest = right;
    }
    
    if (smallest != i) {
        void* temp = bh->array[i];
        bh->array[i] = bh->array[smallest];
        bh->array[smallest] = temp;
        min_heapify(bh, smallest);
    }
}

void binary_heap_free(binary_heap* bh) {
    free(bh->array);
    free(bh);
}