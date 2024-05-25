#include "../engine/include/hashtable.h"
#include "../engine/include/test_hashtable.h"


void test_createHashTable() {
    printf("Testing createHashTable...\n");
    HashTable* hashtable = createHashTable(10);
    assert(hashtable != NULL);
    assert(hashtable->size == 10);
    destroyHashTable(hashtable);
}

void test_destroyHashTable() {
    printf("Testing destroyHashTable...\n");
    HashTable* hashtable = createHashTable(10);
    destroyHashTable(hashtable);
    // Note: It's hard to assert the success of this function as the memory is freed.
    // Just make sure it doesn't cause any errors when run.
}

void test_hash() {
    printf("Testing hash...\n");
    unsigned int hashValue = hash("test", 10);
    assert(hashValue >= 0 && hashValue < 10);
}

void test_insert() {
    printf("Testing insert...\n");
    HashTable* hashtable = createHashTable(10);
    int key = 5;
    int value = 10;
    insert(hashtable, &key, &value, NULL);
    assert(hashtable->table[hash(&key, hashtable->size)]->value == &value);
    destroyHashTable(hashtable);
}

void test_removeFrom() {
    printf("Testing removeFrom...\n");
    HashTable* hashtable = createHashTable(10);
    int key = 5;
    int value = 10;
    insert(hashtable, &key, &value, NULL);
    removeFrom(hashtable, &key);
    assert(hashtable->table[hash(&key, hashtable->size)] == NULL);
    destroyHashTable(hashtable);
}

void test_get() {
    printf("Testing get...\n");
    HashTable* hashtable = createHashTable(10);
    char* key = "key";
    int value = 10;
    insert(hashtable, key, &value, NULL);
    assert(*(int*)get(hashtable, key, strcmp) == value);
    destroyHashTable(hashtable);
}

void test_contains() {
    printf("Testing contains...\n");
    HashTable* hashtable = createHashTable(10);
    char* key = "key";
    int value = 10;
    insert(hashtable, key, &value, NULL);
    assert(contains(hashtable, key, strcmp) == 1);
    destroyHashTable(hashtable);
}

void test_replace() {
    printf("Testing replace...\n");
    HashTable* hashtable = createHashTable(10);
    char* key = "key";
    int value = 10;
    int newValue = 20;
    insert(hashtable, key, &value, NULL);
    replace(hashtable, key, &newValue, NULL, strcmp);
    assert(*(int*)get(hashtable, key, strcmp) == newValue);
    destroyHashTable(hashtable);
}

void test_clear() {
    printf("Testing clear...\n");
    HashTable* hashtable = createHashTable(10);
    char* key = "key";
    int value = 10;
    insert(hashtable, key, &value, NULL);
    clear(hashtable);
    assert(isEmpty(hashtable) == 1);
    destroyHashTable(hashtable);
}

void test_isEmpty() {
    printf("Testing isEmpty...\n");
    HashTable* hashtable = createHashTable(10);
    assert(isEmpty(hashtable) == 1);
    char* key = "key";
    int value = 10;
    insert(hashtable, key, &value, NULL);
    assert(isEmpty(hashtable) == 0);
    destroyHashTable(hashtable);
}

void test_getSize() {
    printf("Testing getSize...\n");
    HashTable* hashtable = createHashTable(10);
    assert(getSize(hashtable) == 10);
    destroyHashTable(hashtable);
}

