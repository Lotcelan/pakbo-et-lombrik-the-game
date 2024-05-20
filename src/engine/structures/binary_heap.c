#include "../include/binary_heap.h"

// binary_heap* binary_heap_create(int capacity, int (*compare)(void*, void*), void (*destroy)(void* v)) {
binary_heap* binary_heap_create(int capacity, int (*compare)(void*, void*)) {
	binary_heap* bh = malloc(sizeof(binary_heap));
	bh->array = (void**)malloc(capacity * sizeof(void*));
    for (int i = 0; i < capacity; i++) {
        bh->array[i] = NULL;
    }
	bh->compare = compare;
	bh->size = 0;
	bh->capacity = capacity;
	// bh->destroy = destroy;

	return bh;
}

void binary_heap_insert(binary_heap* bh, void* value) {
	if (bh->size == bh->capacity) {
		// Resize the array
		bh->capacity = bh->capacity * 2 + 1;
		bh->array = realloc(bh->array, bh->capacity * sizeof(void*));
	}

	bh->size++;
	int i = bh->size - 1;
	bh->array[i] = value;

        printf("%i\n",i);
	while (i != 0 && bh->compare(bh->array[(i - 1) / 2], bh->array[i]) > 0) {
		void* temp = bh->array[i];
		bh->array[i] = bh->array[(i - 1) / 2];
		bh->array[(i - 1) / 2] = temp;
		i = (i - 1) / 2;
        printf(">%i\n",i);
	}
}

void binary_heap_modify(binary_heap* bh, void* to_modify, void* new_value, bool (*cmp)(void* v1, void* v2)) {
	int i = 0;
	while (i < bh->size && !cmp(bh->array[i], to_modify)) {
		i++;
	}

	if (i == bh->size) {
		return;
	}

	bh->array[i] = new_value;

	while (i != 0 && bh->compare(bh->array[(i - 1) / 2], bh->array[i]) > 0) {
		void* temp = bh->array[i];
		bh->array[i] = bh->array[(i - 1) / 2];
		bh->array[(i - 1) / 2] = temp;
		i = (i - 1) / 2;
	}
}

bool is_present_in_binary_heap(binary_heap* bh, void* value, bool (*cmp)(void* v1, void* v2)) {
	for (int i = 0; i < bh->size; i++) {
		if (cmp(bh->array[i], value)) {
			return true;
		}
	}

	return false;
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

int binary_heap_basic_entry_compare(void* e1, void* e2) {
	binary_heap_basic_entry* entry1 = (binary_heap_basic_entry*)e1;
	binary_heap_basic_entry* entry2 = (binary_heap_basic_entry*)e2;
	if (entry1 == NULL && entry2 == NULL) {
		return 0;
	} else if (entry1 == NULL) {
		return 1;
	} else if (entry2 == NULL) {
		return -1;
	} else {
		if (entry1->priority > entry2->priority) {
			return 1;
		} else if (entry1->priority == entry2->priority) {
			return 0;
		} else {
			return -1;
		}
	}
}

bool is_binary_heap_empty(binary_heap* bh) {
	return bh->size == 0;
}

// binary_heap_basic_entry* create_binary_heap_basic_entry(void* value, float priority, void (*destroy)(void* v)) {
binary_heap_basic_entry* create_binary_heap_basic_entry(void* value, float priority) {
	binary_heap_basic_entry* res = (binary_heap_basic_entry*)malloc(sizeof(binary_heap_basic_entry*));
	res->priority = priority;
	res->value = value;
	// res->destroy = destroy;

	return res;
}

void binary_heap_basic_entry_free(void* bhe_void) {
	if (bhe_void == NULL) return;
    binary_heap_basic_entry* bhe = (binary_heap_basic_entry*)bhe_void;
    // printf("destroying %s avec %p\n", bhe->value, bhe->destroy);
    // if (bhe->destroy != NULL) bhe->destroy(bhe->value);
	free(bhe);
}

void binary_heap_free(binary_heap* bh) {
	if (bh == NULL) return;

    // for (int i = bh->size-1; i >=0; i--) {
    //     if (bh->destroy != NULL) bh->destroy((bh->array)[i]);
    // }
    free(bh->array);
    free(bh);
}