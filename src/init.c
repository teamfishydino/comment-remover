#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "comment.h"
#include "init.h"

CommentStyle* comment_styles = NULL;
size_t comment_styles_count = 0;

void init() { initialize_comment_styles(); }

void cleanup() {
  for (size_t i = 0; i < comment_styles_count; i++) {
    comment_style_free(&comment_styles[i]);
  }
  free(comment_styles);
}

void initialize_comment_styles() {
  comment_styles = malloc(LANG_COUNT * sizeof(CommentStyle));
  if (!comment_styles) {
    fprintf(stderr, "Memory Allocation Failed\n");
    exit(EXIT_FAILURE);
  }
  comment_styles_count = LANG_COUNT;

  comment_style_init(&comment_styles[LANG_C], LANG_C);
  comment_style_add_extension(&comment_styles[LANG_C], "c");
  comment_style_add_extension(&comment_styles[LANG_C], "h");
  comment_style_add_single_line_comment(&comment_styles[LANG_C], "//");
  comment_style_add_multi_line_comment(&comment_styles[LANG_C], "/*", "*/");

  comment_style_init(&comment_styles[LANG_CPP], LANG_CPP);
  comment_style_add_extension(&comment_styles[LANG_CPP], "cpp");
  comment_style_add_extension(&comment_styles[LANG_CPP], "hpp");
  comment_style_add_single_line_comment(&comment_styles[LANG_CPP], "//");
  comment_style_add_multi_line_comment(&comment_styles[LANG_CPP], "/*", "*/");

  comment_style_init(&comment_styles[LANG_JAVA], LANG_JAVA);
  comment_style_add_extension(&comment_styles[LANG_JAVA], "java");
  comment_style_add_single_line_comment(&comment_styles[LANG_JAVA], "//");
  comment_style_add_multi_line_comment(&comment_styles[LANG_JAVA], "/*", "*/");

  comment_style_init(&comment_styles[LANG_PYTHON], LANG_PYTHON);
  comment_style_add_extension(&comment_styles[LANG_PYTHON], "py");
  comment_style_add_single_line_comment(&comment_styles[LANG_PYTHON], "#");
  comment_style_add_multi_line_comment(&comment_styles[LANG_PYTHON], "'''", "'''");
  comment_style_add_multi_line_comment(&comment_styles[LANG_PYTHON], "\"\"\"", "\"\"\"");

  comment_style_init(&comment_styles[LANG_JAVASCRIPT], LANG_JAVASCRIPT);
  comment_style_add_extension(&comment_styles[LANG_JAVASCRIPT], "js");
  comment_style_add_single_line_comment(&comment_styles[LANG_JAVASCRIPT], "//");
  comment_style_add_multi_line_comment(&comment_styles[LANG_JAVASCRIPT], "/*", "*/");

  comment_style_init(&comment_styles[LANG_HTML], LANG_HTML);
  comment_style_add_extension(&comment_styles[LANG_HTML], "html");
  comment_style_add_extension(&comment_styles[LANG_HTML], "htm");
  comment_style_add_multi_line_comment(&comment_styles[LANG_HTML], "<!--", "-->");

  comment_style_init(&comment_styles[LANG_CSS], LANG_CSS);
  comment_style_add_extension(&comment_styles[LANG_CSS], "css");
  comment_style_add_multi_line_comment(&comment_styles[LANG_CSS], "/*", "*/");

  comment_style_init(&comment_styles[LANG_RUBY], LANG_RUBY);
  comment_style_add_extension(&comment_styles[LANG_RUBY], "rb");
  comment_style_add_single_line_comment(&comment_styles[LANG_RUBY], "#");
  comment_style_add_multi_line_comment(&comment_styles[LANG_RUBY], "=begin", "=end");

  comment_style_init(&comment_styles[LANG_PHP], LANG_PHP);
  comment_style_add_extension(&comment_styles[LANG_PHP], "php");
  comment_style_add_single_line_comment(&comment_styles[LANG_PHP], "//");
  comment_style_add_single_line_comment(&comment_styles[LANG_PHP], "#");
  comment_style_add_multi_line_comment(&comment_styles[LANG_PHP], "/*", "*/");

  comment_style_init(&comment_styles[LANG_GO], LANG_GO);
  comment_style_add_extension(&comment_styles[LANG_GO], "go");
  comment_style_add_single_line_comment(&comment_styles[LANG_GO], "//");
  comment_style_add_multi_line_comment(&comment_styles[LANG_GO], "/*", "*/");

  comment_style_init(&comment_styles[LANG_RUST], LANG_RUST);
  comment_style_add_extension(&comment_styles[LANG_RUST], "rs");
  comment_style_add_single_line_comment(&comment_styles[LANG_RUST], "//");
  comment_style_add_multi_line_comment(&comment_styles[LANG_RUST], "/*", "*/");

  comment_style_init(&comment_styles[LANG_SWIFT], LANG_SWIFT);
  comment_style_add_extension(&comment_styles[LANG_SWIFT], "swift");
  comment_style_add_single_line_comment(&comment_styles[LANG_SWIFT], "//");
  comment_style_add_multi_line_comment(&comment_styles[LANG_SWIFT], "/*", "*/");

  comment_style_init(&comment_styles[LANG_KOTLIN], LANG_KOTLIN);
  comment_style_add_extension(&comment_styles[LANG_KOTLIN], "kt");
  comment_style_add_single_line_comment(&comment_styles[LANG_KOTLIN], "//");
  comment_style_add_multi_line_comment(&comment_styles[LANG_KOTLIN], "/*", "*/");

  comment_style_init(&comment_styles[LANG_TYPESCRIPT], LANG_TYPESCRIPT);
  comment_style_add_extension(&comment_styles[LANG_TYPESCRIPT], "ts");
  comment_style_add_single_line_comment(&comment_styles[LANG_TYPESCRIPT], "//");
  comment_style_add_multi_line_comment(&comment_styles[LANG_TYPESCRIPT], "/*", "*/");

  comment_style_init(&comment_styles[LANG_SQL], LANG_SQL);
  comment_style_add_extension(&comment_styles[LANG_SQL], "sql");
  comment_style_add_single_line_comment(&comment_styles[LANG_SQL], "--");
  comment_style_add_multi_line_comment(&comment_styles[LANG_SQL], "/*", "*/");

  comment_style_init(&comment_styles[LANG_LUA], LANG_LUA);
  comment_style_add_extension(&comment_styles[LANG_LUA], "lua");
  comment_style_add_single_line_comment(&comment_styles[LANG_LUA], "--");
  comment_style_add_multi_line_comment(&comment_styles[LANG_LUA], "--[[", "]]");

  comment_style_init(&comment_styles[LANG_PERL], LANG_PERL);
  comment_style_add_extension(&comment_styles[LANG_PERL], "pl");
  comment_style_add_extension(&comment_styles[LANG_PERL], "pm");
  comment_style_add_single_line_comment(&comment_styles[LANG_PERL], "#");
  comment_style_add_multi_line_comment(&comment_styles[LANG_PERL], "=pod", "=cut");

  comment_style_init(&comment_styles[LANG_SHELL], LANG_SHELL);
  comment_style_add_extension(&comment_styles[LANG_SHELL], "sh");
  comment_style_add_extension(&comment_styles[LANG_SHELL], "bash");
  comment_style_add_single_line_comment(&comment_styles[LANG_SHELL], "#");

  comment_style_init(&comment_styles[LANG_R], LANG_R);
  comment_style_add_extension(&comment_styles[LANG_R], "r");
  comment_style_add_single_line_comment(&comment_styles[LANG_R], "#");

  comment_style_init(&comment_styles[LANG_MATLAB], LANG_MATLAB);
  comment_style_add_extension(&comment_styles[LANG_MATLAB], "m");
  comment_style_add_single_line_comment(&comment_styles[LANG_MATLAB], "%");
  comment_style_add_multi_line_comment(&comment_styles[LANG_MATLAB], "%{", "%}");
}