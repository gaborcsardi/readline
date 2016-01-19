
#include <Rinternals.h>
#include <stdlib.h>		/* free */
#include "utf8.h"
#include "linenoise.h"

SEXP R_readline_read_line(SEXP prompt, SEXP multiline, SEXP history) {
  char *line;
  SEXP result;

  linenoiseSetEncodingFunctions(
    linenoiseUtf8PrevCharLen,
    linenoiseUtf8NextCharLen,
    linenoiseUtf8ReadCode);

  if (!isNull(history)) linenoiseHistoryLoad(CHAR(STRING_ELT(history, 0)));

  linenoiseSetMultiLine(LOGICAL(multiline)[0]);
  line = linenoise(CHAR(STRING_ELT(prompt, 0)));

  result = mkString(line);
  free(line);

  return result;
}
