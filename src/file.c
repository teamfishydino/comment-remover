#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "language.h"
#include "string/string.h"
#include "string/vector.h"
#include "comment.h"
#include "file.h"

extern CommentStyle* comment_styles;

void process_file(const char* input_filename, const char* output_filename) {
  FILE* input_file = fopen(input_filename, "r");
  if (!input_file) {
    fprintf(stderr, "Unable to open an input file: %s\n", input_filename);
    return;
  }

  FILE* output_file = fopen(output_filename, "w");
  if (!output_file) {
    fprintf(stderr, "Unable to generate an output file: %s\n", output_filename);
    fclose(input_file);
    return;
  }

  Language lang = detect_language(input_filename);
  if (lang == LANG_UNKNOWN) {
    fprintf(stderr, "The file type is not supported: %s\n", input_filename);
    fclose(input_file);
    fclose(output_file);
    return;
  }

  const CommentStyle* style = &comment_styles[lang];
  bool in_multi_line_comment = false;
  size_t current_multi_line_index = 0;

  string line;
  string_init(&line);

  char buffer[1024];
  while (fgets(buffer, sizeof(buffer), input_file) != NULL) {
    string_append(&line, buffer);
    
    if (string_ends_with(buffer, "\n")) {
      remove_comments(&line, style, &in_multi_line_comment, &current_multi_line_index);
      fputs(line.data, output_file);
      string_free(&line);
      string_init(&line);
    }
  }

  if (line.length > 0) {
    remove_comments(&line, style, &in_multi_line_comment, &current_multi_line_index);
    fputs(line.data, output_file);
  }

  string_free(&line);
  fclose(input_file);
  fclose(output_file);
  printf("The comments in file %s have been removed and saved to file %s.\n", input_filename, output_filename);
}

bool is_valid_filename(const char* filename) {
  size_t len = strlen(filename);
  if (len == 0 || len > 255) {
    return false;
  }
  for (size_t i = 0; i < len; i++) {
    if (!isalnum(filename[i]) && filename[i] != '.' && filename[i] != '_' && filename[i] != '-') {
      return false;
    }
  }
  return true;
}