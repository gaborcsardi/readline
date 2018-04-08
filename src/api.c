
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

#include "replxx.h"

SEXP read_line(SEXP prompt) {

  Replxx* replxx = replxx_init();
  replxx_install_window_change_handler(replxx);

  const char* cresult = replxx_input(replxx, CHAR(STRING_ELT(prompt, 0)));

  if (!cresult) return R_NilValue;

  replxx_end(replxx);
  return mkString(cresult);
}


static const R_CallMethodDef callMethods[]  = {
  {"read_line", (DL_FUNC) &read_line, 1},
  {NULL, NULL, 0}
};


void R_init_lines(DllInfo *dll) {
  R_registerRoutines(dll, NULL, callMethods, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  R_forceSymbols(dll, TRUE);
}
