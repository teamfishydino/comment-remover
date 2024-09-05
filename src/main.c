#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include "comment.h"
#include "init.h"
#include "file.h"

extern CommentStyle* comment_styles;
extern size_t comment_styles_count;

void print_usage(const char* program_name) {
  printf("Usage: %s <input_file> <output_file>\n", program_name);
  printf("Supported file extensions:");
  for (size_t i = 0; i < comment_styles_count; i++) {
    for (size_t j = 0; j < comment_styles[i].extensions.size; j++) {
      printf("  .%s", comment_styles[i].extensions.items[j].data);
      if (j < comment_styles[i].extensions.size - 1) {
        printf(", ");
      }
    }
    printf("\n");
  }
}

int main(int argc, char* argv[]) {
  init();
  if (argc < 3) {
    print_usage(argv[0]);
    return 1;
  }

  const char* input_filename = argv[1];
  const char* output_filename = argv[2];

  if (!is_valid_filename(input_filename) || !is_valid_filename(output_filename)) {
    fprintf(stderr, "Invalid file name. Only alphabets, numbers, '.', '_', and '-' are allowed.\n");
    return 1;
  }

  process_file(input_filename, output_filename);
  cleanup();

  return 0;
}