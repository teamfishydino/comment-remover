#include <stdio.h>
#include <stdlib.h>
#include "string/string.h"
#include "string/vector.h"

void string_vector_init(StringVector* vec) {
  vec->items = (string*)malloc(sizeof(string));
  vec->size = 0;
  vec->capacity = 1;
}

void string_vector_free(StringVector* vec) {
  for (size_t i = 0; i < vec->size; i++) {
    string_free(&vec->items[i]);
  }
  free(vec->items);
  vec->items = NULL;
  vec->size = 0;
  vec->capacity = 0;
}

void string_vector_expand(StringVector* vec, size_t new_capacity) {
  if (new_capacity > vec->capacity) {
    string* new_items = realloc(vec->items, new_capacity * sizeof(string));
    if (!new_items) {
      fprintf(stderr, "Memory Allocation Failed\n");
      exit(EXIT_FAILURE);
    }
    vec->items = new_items;
    vec->capacity = new_capacity;
  }
}

void string_vector_push(StringVector* vec, const string* item) {
  if (vec->size == vec->capacity) {
    size_t new_capacity = vec->capacity == 0 ? 1 : vec->capacity * 2;
    string_vector_expand(vec, new_capacity);
  }

  string_init(&vec->items[vec->size]);
  string_copy(&vec->items[vec->size], item);
  vec->size++;
}