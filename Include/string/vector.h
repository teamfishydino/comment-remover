#ifndef __COMMENT_REMOVER_INCLUDE_STRING_VECTOR_H__
#define __COMMENT_REMOVER_INCLUDE_STRING_VECTOR_H__
#include <stddef.h>
#include "string/string.h"

typedef struct {
  string* items;
  size_t size;
  size_t capacity;
} StringVector;

void string_vector_init(StringVector* vec);
void string_vector_free(StringVector* vec);
void string_vector_expand(StringVector* vec, size_t new_capacity);
void string_vector_push(StringVector* vec, const string* item);
#endif