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
    void (*destroy)(void* value);
} Entry;

typedef struct HashTable {
    int size;
    Entry** table;
} HashTable;

HashTable* createHashTable(int size);
void destroyHashTable(HashTable* hashtable);
void insert(HashTable* hashtable, void* key, void* value, void (*destroy)(void* value));
void replace(HashTable* hashtable, const char* key, void* value, void (*destroy)(void* value), int (*cmp)(const char*, const char*));
void removeFrom(HashTable* hashtable, void* key);
void* get(HashTable* hashtable, const char* key, int (*cmp)(const char*, const char*));
int contains(HashTable* hashtable, void* key, int (*cmp)(const char*, const char*));
void clear(HashTable* hashtable);
int isEmpty(HashTable* hashtable);
int getSize(HashTable* hashtable);
void displayHashTableResource(HashTable* hashtable);
void printKeys(HashTable* hashtable);

#endif
