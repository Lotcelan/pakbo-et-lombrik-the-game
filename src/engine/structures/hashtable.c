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
            if (entry->destroy) entry->destroy(entry);
            entry = next;
        }
    }

    free(hashtable->table);
    free(hashtable);
}

unsigned int hash(const char* key, int size) {
    if (key == NULL) {
        printf("HASH D'UNE CLE NULLE, C PAS NORMALE\n");
        return 0;
    }
    
    unsigned char* str = (unsigned char*)key;
    unsigned int hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % size;
}


void insert(HashTable* hashtable, void* key, void* value, void (*destroy)(void*)) {
    unsigned int index = hash(key, hashtable->size);
    Entry* entry = (Entry*)malloc(sizeof(Entry));
    entry->key = key;
    entry->value = value;
    entry->next = hashtable->table[index];
    entry->destroy = destroy;
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
    if (key == NULL) {
        return NULL;
    }
    
    unsigned int index = hash(key, hashtable->size);
    Entry* entry = hashtable->table[index];

    while (entry != NULL) {
        // printf("%s\n", entry->key);
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

void replace(HashTable* hashtable, const char* key, void* value, void (*destroy)(void* value), int (*cmp)(const char*, const char*)) {
    if (hashtable == NULL) {
        return;
    }
    unsigned int index = hash(key, hashtable->size);
    Entry* entry = hashtable->table[index];

    while (entry != NULL) {
        if (cmp(entry->key, key) == 0) {
            if (entry->destroy != NULL) {
                // printf("Destroying %p\n", entry->value);
                entry->destroy(entry->value);
            }
            entry->value = value;
            entry->destroy = destroy;
            return;
        }
        entry = entry->next;
    }
}

void clear(HashTable* hashtable) {
    if (hashtable == NULL) {
        return;
    }
    
    for (int i = 0; i < hashtable->size; i++) {
        Entry* entry = hashtable->table[i];
        while (entry != NULL) {
            Entry* next = entry->next;
            if (entry->destroy != NULL) {
                entry->destroy(entry);
            }
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

void printKeys(HashTable* hashtable) {
    for (int i = 0; i < hashtable->size; i++) {
        Entry* entry = hashtable->table[i];
        printf("Bucket %d: ", i);
        while (entry != NULL) {
            printf("%s, ", (char*)entry->key);
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
