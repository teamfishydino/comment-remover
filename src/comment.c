#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "string/string.h"
#include "string/vector.h"
#include "comment.h"

void comment_style_init(CommentStyle* style, Language lang) {
  style->language = lang;
  string_vector_init(&style->extensions);
  string_vector_init(&style->single_line);
  string_vector_init(&style->multi_line_start);
  string_vector_init(&style->multi_line_end);
}

void comment_style_free(CommentStyle* style) {
  string_vector_free(&style->extensions);
  string_vector_free(&style->single_line);
  string_vector_free(&style->multi_line_start);
  string_vector_free(&style->multi_line_end);
}

void comment_style_add_extension(CommentStyle* style, const char* ext) {
  string str;
  string_init(&str);
  string_append(&str, ext);
  string_vector_push(&style->extensions, &str);
  string_free(&str);
}

void comment_style_add_single_line_comment(CommentStyle* style, const char* marker) {
  string str;
  string_init(&str);
  string_append(&str, marker);
  string_vector_push(&style->single_line, &str);
  string_free(&str);
}

void comment_style_add_multi_line_comment(CommentStyle* style, const char* start, const char* end) {
  string str_start, str_end;
  string_init(&str_start);
  string_init(&str_end);
  string_append(&str_start, start);
  string_append(&str_end, end);
  string_vector_push(&style->multi_line_start, &str_start);
  string_vector_push(&style->multi_line_end, &str_end);
  string_free(&str_start);
  string_free(&str_end);
}

void remove_comments(string* line, const CommentStyle* style, bool* in_multi_line_comment, size_t* current_multi_line_index) {
  string result;
  string_init(&result);

  size_t i = 0;
  bool found_comment = false;
  while (i < line->length) {
    if (*in_multi_line_comment) {
      bool found_end = false;
      for (size_t j = 0; j < style->multi_line_end.size; j++) {
        if (string_starts_with(line->data + i, style->multi_line_end.items[j].data)) {
          i += style->multi_line_end.items[j].length;
          *in_multi_line_comment = false;
          *current_multi_line_index = 0;
          found_end = true;
          break;
        }
      }
      if (!found_end) {
        i++;
      }
    } else {
      for (size_t j = 0; j < style->single_line.size; j++) {
        if (string_starts_with(line->data + i, style->single_line.items[j].data)) {
          found_comment = true;
          break;
        }
      }

      if (!found_comment) {
        for (size_t j = 0; j < style->multi_line_start.size; j++) {
          if (string_starts_with(line->data + i, style->multi_line_start.items[j].data)) {
            *in_multi_line_comment = true;
            *current_multi_line_index = j;
            i += style->multi_line_start.items[j].length;
            found_comment = true;
            break;
          }
        }
      }

      if (found_comment) {
        while (i > 0 && isspace(result.data[result.length - 1])) {
          result.length--;
        }
        break;
      } else {
        string_append(&result, (char[2]){line->data[i], '\0'});
        i++;
      }
    }
  }

  if (line->length > 0 && line->data[line->length - 1] == '\n') {
    string_append(&result, "\n");
  }

  string_free(line);
  *line = result;
}