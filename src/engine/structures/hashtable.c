#include "../include/hashtable.h"
#include "../include/assets.h"

HashTable* createHashTable(int size) {
    HashTable* hashtable = (HashTable*)malloc(sizeof(HashTable));
    hashtable->size = size;
    hashtable->table = (Entry**)calloc(size, sizeof(Entry*));
    return hashtable;
}

void destroyHashTable(HashTable* hashtable) {
    if (hashtable == NULL) {
        return;
    }

    for (int i = 0; i < hashtable->size; i++) {
        Entry* entry = hashtable->table[i];
        while (entry != NULL) {
            Entry* next = entry->next;
            free(entry);
            entry = next;
        }
    }

    free(hashtable->table);
    free(hashtable);
}

unsigned int hash(const char* key, int size) {
    unsigned char* str = (unsigned char*)key;
    unsigned int hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % size;
}


void insert(HashTable* hashtable, void* key, void* value) {
    unsigned int index = hash(key, hashtable->size);
    Entry* entry = (Entry*)malloc(sizeof(Entry));
    entry->key = key;
    entry->value = value;
    entry->next = hashtable->table[index];
    hashtable->table[index] = entry;
}

void removeFrom(HashTable* hashtable, void* key) {
    unsigned int index = hash(key, hashtable->size);
    Entry* entry = hashtable->table[index];
    Entry* prev = NULL;

    while (entry != NULL) {
        if (entry->key == key) {
            if (prev == NULL) {
                hashtable->table[index] = entry->next;
            } else {
                prev->next = entry->next;
            }
            free(entry);
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

void* get(HashTable* hashtable, const char* key, int (*cmp)(const char*, const char*)) {
    unsigned int index = hash(key, hashtable->size);
    Entry* entry = hashtable->table[index];

    while (entry != NULL) {
        if (cmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }

    return NULL;
}

int contains(HashTable* hashtable, void* key, int (*cmp)(const char*, const char*)) {
    return get(hashtable, key, cmp) != NULL;
}

void clear(HashTable* hashtable) {
    for (int i = 0; i < hashtable->size; i++) {
        Entry* entry = hashtable->table[i];
        while (entry != NULL) {
            Entry* next = entry->next;
            free(entry);
            entry = next;
        }
        hashtable->table[i] = NULL;
    }
}

int isEmpty(HashTable* hashtable) {
    for (int i = 0; i < hashtable->size; i++) {
        if (hashtable->table[i] != NULL) {
            return 0;
        }
    }
    return 1;
}

int getSize(HashTable* hashtable) {
    return hashtable->size;
}

void printImageArray(const unsigned char* arr) {
    printf("(seulement 10 élem) : {"); 
    for (int i = 0; i < 10; i++) {
        printf("%d, ", arr[i]);
    }
    printf("};\n");
}

void displayHashTableResource(HashTable* hashtable) {
    for (int i = 0; i < hashtable->size; i++) {
        Entry* entry = hashtable->table[i];
        printf("Bucket %d: ", i);
        while (entry != NULL) {
            printf("(%s, %d | ", (char*)entry->key, ((MemTexture*)entry->value)->size);
            printImageArray((unsigned char*)((MemTexture*)entry->value)->data);
            printf(") ");
            entry = entry->next;
        }
        printf("\n");
    }
}

// int main() {
//     HashTable* hashtable = createHashTable(10);
//     int key = 5;
//     int value = 10;
//     insert(hashtable, &key, &value);
//     printf("%d\n", *(int*)get(hashtable, &key));
//     remove(hashtable, &key);
//     printf("%d\n", contains(hashtable, &key));
//     destroyHashTable(hashtable);
//     return 0;
// }
