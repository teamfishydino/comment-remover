#ifndef __COMMENT_REMOVER_INCLUDE_COMMENT_H__
#define __COMMENT_REMOVER_INCLUDE_COMMENT_H__
#include <stddef.h>
#include <stdbool.h>
#include "language.h"
#include "string/string.h"
#include "string/vector.h"

typedef struct {
  string marker;
} CommentMarker;

typedef struct {
  Language language;
  StringVector extensions;
  StringVector single_line;
  StringVector multi_line_start;
  StringVector multi_line_end;
} CommentStyle;

void comment_style_init(CommentStyle* style, Language lang);
void comment_style_free(CommentStyle* style);
void comment_style_add_extension(CommentStyle* style, const char* ext);
void comment_style_add_single_line_comment(CommentStyle* style, const char* marker);
void comment_style_add_multi_line_comment(CommentStyle* style, const char* start, const char* end);
void remove_comments(string* line, const CommentStyle* style, bool* in_multi_line_comment, size_t* current_multi_line_index);
#endif