#ifndef __COMMENT_REMOVER_INCLUDE_LANGUAGE_H__
#define __COMMENT_REMOVER_INCLUDE_LANGUAGE_H__
typedef enum {
  LANG_UNKNOWN,
  LANG_C,
  LANG_CPP,
  LANG_JAVA,
  LANG_PYTHON,
  LANG_JAVASCRIPT,
  LANG_HTML,
  LANG_CSS,
  LANG_RUBY,
  LANG_PHP,
  LANG_GO,
  LANG_RUST,
  LANG_SWIFT,
  LANG_KOTLIN,
  LANG_TYPESCRIPT,
  LANG_SQL,
  LANG_LUA,
  LANG_PERL,
  LANG_SHELL,
  LANG_R,
  LANG_MATLAB,
  LANG_COUNT
} Language;

Language detect_language(const char* filename);
#endif