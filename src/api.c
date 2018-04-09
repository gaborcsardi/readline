
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

#include <string.h>

#include "replxx/replxx.h"

void completion_hook(char const* prefix, int bp,
		     replxx_completions* lc, void* ud) {
  SEXP str = (SEXP) ud;
  size_t i, n = LENGTH(str);
  size_t len = strlen(prefix);
  for (i = 0; i < n; i++) {
    const char *s = CHAR(STRING_ELT(str, i));
    if (! strncmp(prefix, s, len)) replxx_add_completion(lc, s);
  }
}

void hint_hook(char const* prefix, int bp, replxx_hints* lc,
	       ReplxxColor* c, void* ud) {
  SEXP str = (SEXP) ud;
  size_t i, n = LENGTH(str);
  size_t len = strlen(prefix);
  for (i = 0; i < n; i++) {
    const char *s = CHAR(STRING_ELT(str, i));
    if (! strncmp(prefix, s, len)) replxx_add_hint(lc, s + len);
  }
}

SEXP read_line(SEXP prompt, SEXP default_, SEXP history, SEXP completions,
	       SEXP show_hints, SEXP tab_complete) {

  SEXP result = R_NilValue;
  Replxx* replxx = replxx_init();
  const char *c_history = isNull(history) ? 0 : CHAR(STRING_ELT(history, 0));
  const char *c_default = CHAR(STRING_ELT(default_, 0));
  replxx_install_window_change_handler(replxx);

  if (c_history) {
    if (replxx_history_load(replxx, c_history)) {
      replxx_end(replxx);
      error("Cannot open history file");
    }
  }

  replxx_set_preload_buffer(replxx, c_default);

  if (LOGICAL(show_hints)[0]) {
    replxx_set_hint_callback(replxx, hint_hook, completions);
  }
  if (LOGICAL(tab_complete)[0]) {
    replxx_set_completion_callback(replxx, completion_hook, completions);
  }

  const char* c_result = replxx_input(replxx, CHAR(STRING_ELT(prompt, 0)));

  if (!c_result) goto cleanup;

  result = mkString(c_result);
  replxx_history_add(replxx, c_result);
  if (c_history) replxx_history_save(replxx, c_history);

 cleanup:
  replxx_end(replxx);
  return result;
}


void rreplxx_finalizer(SEXP x) {
  Replxx* replxx = (Replxx*) R_ExternalPtrAddr(x);
  if (replxx) replxx_end(replxx);
  R_SetExternalPtrAddr(x, 0);
}


SEXP rreplxx_new() {
  Replxx* replxx = replxx_init();
  SEXP res;
  if (!replxx) error("Could not create new replxx");
  res = PROTECT(R_MakeExternalPtr(replxx, R_NilValue, R_NilValue));
  setAttrib(res, R_ClassSymbol, mkString("replxx"));
  R_RegisterCFinalizerEx(res, rreplxx_finalizer, /* onexit = */ 1);
  UNPROTECT(1);
  return res;
}


SEXP rreplxx_set_highlighter(SEXP replxx, SEXP fun) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_set_completion(SEXP replxx, SEXP fun) {
  /* TODO */
  return R_NilValue;

}

SEXP rreplxx_add_completions(SEXP completions, SEXP strings) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_set_hinter(SEXP replxx, SEXP fun) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_add_hints(SEXP hints, SEXP strings) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_input(SEXP replxx, SEXP prompt) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_print(SEXP replxx, SEXP fmt, SEXP args) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_set_preload(SEXP replxx, SEXP text) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_history_add(SEXP replxx, SEXP lines) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_history_size(SEXP replxx) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_set_word_break_characters(SEXP replxx, SEXP chars) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_set_special_prefixes(SEXP replxx, SEXP specials) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_set_max_line_size(SEXP replxx, SEXP len) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_set_max_hint_rows(SEXP replxx, SEXP count) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_set_double_tab_completion(SEXP replxx, SEXP on) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_set_complete_on_empty(SEXP replxx, SEXP on) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_set_beep_on_ambiguous_completion(SEXP replxx, SEXP on) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_set_no_color(SEXP replxx, SEXP on) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_set_max_history_size(SEXP replxx, SEXP len) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_get_history_line(SEXP replxx, SEXP index) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_save_history(SEXP replxx, SEXP path) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_load_history(SEXP replxx, SEXP path) {
  /* TODO */
  return R_NilValue;
}

SEXP rreplxx_clear_screen(SEXP replxx) {
  /* TODO */
  return R_NilValue;
}


static const R_CallMethodDef callMethods[]  = {
  {"read_line", (DL_FUNC) &read_line, 6},
  {"rreplxx_new", (DL_FUNC) &rreplxx_new, 0},
  {"rreplxx_set_highlighter", (DL_FUNC) &rreplxx_set_highlighter, 2},
  {"rreplxx_set_completion", (DL_FUNC) &rreplxx_set_completion, 2},
  {"rreplxx_add_completions", (DL_FUNC) &rreplxx_add_completions, 2},
  {"rreplxx_set_hinter", (DL_FUNC) &rreplxx_set_hinter, 2},
  {"rreplxx_add_hints", (DL_FUNC) &rreplxx_add_hints, 2},
  {"rreplxx_input", (DL_FUNC) &rreplxx_input, 2},
  {"rreplxx_print", (DL_FUNC) &rreplxx_print, 3},
  {"rreplxx_set_preload", (DL_FUNC) &rreplxx_set_preload, 2},
  {"rreplxx_history_add", (DL_FUNC) &rreplxx_history_add, 2},
  {"rreplxx_history_size", (DL_FUNC) &rreplxx_history_size, 1},
  {"rreplxx_set_word_break_characters",
   (DL_FUNC) &rreplxx_set_word_break_characters, 2},
  {"rreplxx_set_special_prefixes", (DL_FUNC) &rreplxx_set_special_prefixes, 2},
  {"rreplxx_set_max_line_size", (DL_FUNC) &rreplxx_set_max_line_size, 2},
  {"rreplxx_set_max_hint_rows", (DL_FUNC) &rreplxx_set_max_hint_rows, 2},
  {"rreplxx_set_double_tab_completion",
   (DL_FUNC) &rreplxx_set_double_tab_completion, 2},
  {"rreplxx_set_complete_on_empty",
   (DL_FUNC) &rreplxx_set_complete_on_empty, 2},
  {"rreplxx_set_beep_on_ambiguous_completion",
   (DL_FUNC) &rreplxx_set_beep_on_ambiguous_completion, 2},
  {"rreplxx_set_no_color", (DL_FUNC) &rreplxx_set_no_color, 2},
  {"rreplxx_set_max_history_size", (DL_FUNC) &rreplxx_set_max_history_size, 2},
  {"rreplxx_get_history_line", (DL_FUNC) &rreplxx_get_history_line, 2},
  {"rreplxx_save_history", (DL_FUNC) &rreplxx_save_history, 2},
  {"rreplxx_load_history", (DL_FUNC) &rreplxx_load_history, 2},
  {"rreplxx_clear_screen", (DL_FUNC) &rreplxx_clear_screen, 1},
  {NULL, NULL, 0}
};


void R_init_lines(DllInfo *dll) {
  R_registerRoutines(dll, NULL, callMethods, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  R_forceSymbols(dll, TRUE);
}
