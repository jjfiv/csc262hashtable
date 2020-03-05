#include "assoc_list.h"
#include <stdlib.h> // malloc, free

// Construct a new association list (completed).
AssocList_t* assoc_new(void) {
	AssocList_t* self = malloc(sizeof(AssocList_t));
	assert(self != NULL);
	self->num_elements = 0;
	self->head = NULL;
	return self;
}

// Put a (key, value) pair into this list, overriding previous versions of the key if applicable.
void assoc_put(AssocList_t* self, bytes_t* key, bytes_t* value) {
	assert(self != NULL);
	assert(key != NULL);
	assert(value != NULL);

	// TODO: finish this method.
	printf("called assoc_put: ");
	bytes_print(stdout, key);
	printf(" ");
	bytes_print(stdout, value);
	printf("\n");

	for (AssocEntry_t* n = self->head; n != NULL; n = n->next) {
		if (bytes_equal(key, n->key)) {
			bytes_free(n->value);
			bytes_free(key);
			n->value = value;
			return;
		}
	}
	// Not found:
	AssocEntry_t* node = malloc(sizeof(AssocEntry_t));
	node->next = self->head;
	node->key = key;
	node->value = value;
	self->num_elements++;
	self->head = node;
}

// Remove an entry matching this key in the association list.
void assoc_remove(AssocList_t* self, bytes_t* key) {
	assert(self != NULL);
	assert(key != NULL);

	// TODO: finish this method.
	printf("called assoc_remove: ");
	bytes_println(stdout, key);
	
	AssocEntry_t** prev = &self->head;
	for (AssocEntry_t* n = *prev; n != NULL; n = n->next) {
		if (bytes_equal(key, n->key)) {
			*prev = n->next;
			bytes_free(n->value);
			bytes_free(n->key);
			free(n);
			self->num_elements--;
			return;
		}
		prev = &(n->next);
	}
}

// Lookup an entry matching this key and return a pointer to its value.
bytes_t* assoc_get(AssocList_t* self, bytes_t* key) {
	assert(self != NULL);
	assert(key != NULL);

	printf("called assoc_get: ");
	bytes_println(stdout, key);
	
	for (AssocEntry_t* n = self->head; n != NULL; n = n->next) {
		if (bytes_equal(key, n->key)) {
			return n->value;
		}
	}

	// TODO: finish this method; return NULL if missing!
	return NULL;
}

// Remove all entries from this list (try to free in the right places!)
void assoc_clear(AssocList_t* self) {
	assert(self != NULL);

	AssocEntry_t* current = self->head;
	AssocEntry_t* next = NULL;
	while(current != NULL) {
		// grab next:
		next = current->next;
		// delete current:
		bytes_free(current->key);
		bytes_free(current->value);
		free(current);
		// move to next
		current = next;
	}

	// Finish clearing data:
	self->num_elements = 0;
	self->head = NULL;
}

// Lookup the number of elements in this data structure; prefer O(1) to O(n).
size_t assoc_size(AssocList_t* self) {
	assert(self != NULL);
	return self->num_elements;
}
