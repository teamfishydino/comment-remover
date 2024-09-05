#ifndef __COMMENT_REMOVER_INCLUDE_STRING_H__
#define __COMMENT_REMOVER_INCLUDE_STRING_H__
#include <stddef.h>
#include <stdbool.h>

typedef struct {
  char* data;
  size_t length;
  size_t capacity;
} string;

void string_init(string* str);
string* __new_string();
void string_free(string* str);
void string_expand(string* str, size_t new_capacity);
void string_append(string* str, const char* append);
void string_copy(string* dest, const string* src);
bool string_starts_with(const char* str, const char* prefix);
bool string_ends_with(const char* str, const char* suffix);
#endif