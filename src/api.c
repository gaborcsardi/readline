
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


static const R_CallMethodDef callMethods[]  = {
  {"read_line", (DL_FUNC) &read_line, 6},
  {NULL, NULL, 0}
};


void R_init_lines(DllInfo *dll) {
  R_registerRoutines(dll, NULL, callMethods, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  R_forceSymbols(dll, TRUE);
}
