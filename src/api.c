
#include <Rinternals.h>
#include <stdlib.h>		/* free */
#include <string.h>
#include "utf8.h"
#include "linenoise.h"

static SEXP R_readline_completions;

void R_readline_completion(const char *buf, linenoiseCompletions *lc) {
  int i, n = LENGTH(R_readline_completions);
  int len = strlen(buf);
  for (i = 0; i < n; i++) {
    const char *c = CHAR(STRING_ELT(R_readline_completions, i));
    if (!strncmp(buf, c, len)) { linenoiseAddCompletion(lc, c); }
  }
}

SEXP R_readline_read_line(SEXP prompt, SEXP multiline, SEXP history,
			  SEXP completions) {
  char *line;
  SEXP result;

  linenoiseSetEncodingFunctions(
    linenoiseUtf8PrevCharLen,
    linenoiseUtf8NextCharLen,
    linenoiseUtf8ReadCode);

  if (!isNull(history)) linenoiseHistoryLoad(CHAR(STRING_ELT(history, 0)));
  if (!isNull(completions)) {
    R_readline_completions = completions;
    linenoiseSetCompletionCallback(R_readline_completion);
  }

  linenoiseSetMultiLine(LOGICAL(multiline)[0]);
  line = linenoise(CHAR(STRING_ELT(prompt, 0)));

  result = ScalarString(mkCharCE(line, CE_UTF8));
  free(line);

  return result;
}
