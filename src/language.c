#include <stdio.h>
#include <string.h>
#include "language.h"
#include "comment.h"

extern CommentStyle* comment_styles;
extern size_t comment_styles_count;

Language detect_language(const char* filename) {
  const char* extension = strrchr(filename, '.');
  if (!extension) {
    return LANG_UNKNOWN;
  }
  extension++;

  for (size_t i = 0; i < comment_styles_count; i++) {
    for (size_t j = 0; j < comment_styles[i].extensions.size; j++) {
      if (strcasecmp(extension, comment_styles[i].extensions.items[j].data) == 0) {
        return comment_styles[i].language;
      }
    }
  }

  return LANG_UNKNOWN;
}
