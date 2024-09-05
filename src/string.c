#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "string/string.h"

void string_init(string* str) {
  str->data = (char*)malloc(1);
  str->length = 0;
  str->capacity = 1;
}

string* __new_string() {
  string* str = (string*)malloc(sizeof(string));
  if (!str) {
    return NULL;
  }
  str->data = (char*)malloc(1);
  if (!str->data) {
    free(str);
    return NULL;
  }
  str->length = 0;
  str->capacity = 1;
  str->data[0] = '\0';
  return str;
}

void string_free(string* str) {
  free(str->data);
  str->data = NULL;
  str->length = 0;
  str->capacity = 0;
}

void string_expand(string* str, size_t new_capacity) {
  if (new_capacity > str->capacity) {
    char* new_data = realloc(str->data, new_capacity);
    if (!new_data) {
      fprintf(stderr, "Memory Allocation Failed\n");
      exit(EXIT_FAILURE);
    }
    str->data = new_data;
    str->capacity = new_capacity;
  }
}

void string_append(string* str, const char* append) {
  if (str == NULL || str->data == NULL) {
    fprintf(stderr, "The string is not initialized\n");
    exit(EXIT_FAILURE);
  }
  
  size_t append_len = strlen(append);
  size_t new_length = str->length + append_len;
  string_expand(str, new_length + 1);
  memcpy(str->data + str->length, append, append_len);
  str->data[new_length] = '\0';
  str->length = new_length;
}

void string_copy(string* dest, const string* src) {
  string_expand(dest, src->length + 1);
  memcpy(dest->data, src->data, src->length + 1);
  dest->length = src->length;
}

bool string_starts_with(const char* str, const char* prefix) {
  return strncmp(str, prefix, strlen(prefix)) == 0;
}

bool string_ends_with(const char* str, const char* suffix) {
  size_t str_len = strlen(str);
  size_t suffix_len = strlen(suffix);
  if (suffix_len > str_len) {
    return false;
  }
  return strncmp(str + str_len - suffix_len, suffix, suffix_len) == 0;
}