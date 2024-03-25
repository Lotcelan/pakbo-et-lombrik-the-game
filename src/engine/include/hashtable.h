#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct MemTexture MemTexture;

typedef struct Entry {
    void* key;
    void* value;
    struct Entry* next;
} Entry;

typedef struct HashTable {
    int size;
    Entry** table;
} HashTable;

HashTable* createHashTable(int size);
void destroyHashTable(HashTable* hashtable);
void insert(HashTable* hashtable, void* key, void* value);
void removeFrom(HashTable* hashtable, void* key);
void* get(HashTable* hashtable, void* key, int (*cmp)(const char*, const char*));
int contains(HashTable* hashtable, void* key, int (*cmp)(void*, void*));
void clear(HashTable* hashtable);
int isEmpty(HashTable* hashtable);
int getSize(HashTable* hashtable);
void displayHashTableResource(HashTable* hashtable);

#endif