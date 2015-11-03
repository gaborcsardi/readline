
#include <Rinternals.h>
#include <stdlib.h>		/* free */
#include "utf8.h"
#include "linenoise.h"

SEXP R_readline_read_line(SEXP prompt) {
  char *line;
  SEXP result;

  linenoiseSetEncodingFunctions(
    linenoiseUtf8PrevCharLen,
    linenoiseUtf8NextCharLen,
    linenoiseUtf8ReadCode);

  line = linenoise(CHAR(STRING_ELT(prompt, 0)));

  result = mkString(line);

  free(line);

  return result;
}
