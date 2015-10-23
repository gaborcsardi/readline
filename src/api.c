
#include <Rinternals.h>
#include <stdlib.h>		/* free */
#include "linenoise.h"

SEXP R_linenoise_read_line(SEXP prompt, SEXP pprompt) {
  char *line = linenoise(CHAR(STRING_ELT(prompt, 0)),
			 CHAR(STRING_ELT(pprompt, 0)));
  SEXP result = mkString(line);
  free(line);
  return result;
}
