
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

#include "replxx/replxx.h"

SEXP read_line(SEXP prompt, SEXP history) {

  SEXP result = R_NilValue;
  Replxx* replxx = replxx_init();
  const char *c_history = isNull(history) ? 0 : CHAR(STRING_ELT(history, 0));
  replxx_install_window_change_handler(replxx);

  if (c_history) {
    if (replxx_history_load(replxx, c_history)) {
      replxx_end(replxx);
      error("Cannot open history file");
    }
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
  {"read_line", (DL_FUNC) &read_line, 2},
  {NULL, NULL, 0}
};


void R_init_lines(DllInfo *dll) {
  R_registerRoutines(dll, NULL, callMethods, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  R_forceSymbols(dll, TRUE);
}
