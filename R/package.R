
#' Read a line from the terminal
#'
#' @param prompt A string that is printed at the beginning of the
#'   line of the user input. Ideally it should be short, so there
#'   is enough space for the input. It can be colored and styled
#'   with ANSI escape sequences from the \code{crayon} package.
#' @param multiline Whether to use multi-line mode. This is ignored
#'   on unsupported terminals, those work similarly to multi-line
#'   mode, anyway.
#' @param history If not \code{NULL}, then it must be a character
#'   scalar, the name of the file that is used as a browseable history. The
#'   newly entered entry is added to this file. Note that history
#'   might not be supported by the \code{base::readline} fallback
#'   method.
#' @param completions A character vector of possible TAB-completions.
#'   Ignored on unsupported terminals that use the \code{base::readline}
#'   fallback mechanism.
#' @return A character scalar, the string that was read.
#'
#' @export
#' @useDynLib readline R_readline_read_line
#' @examples
#' \dontrun{
#'   read_line(prompt = "what> ")
#'
#'   ## History files
#'   hist <- tempfile()
#'   cat("previous entry\n", file = hist, append = TRUE)
#'   cat("another entry\n", file = hist, append = TRUE)
#'   read_line(prompt = "what> ", history = hist)
#'
#'   ## The new entry is added to the history file
#'   readLines(hist)
#'
#'   ## TAB-completion
#'   read_line(prompt = "what> ", completions = c("foobar", "foo", "bar"))
#' }

read_line <- function(prompt = "", multiline = FALSE, history = NULL,
                      completions = NULL) {

  prompt <- as_string(prompt)
  multiline <- as_flag(multiline)
  if (!is.null(history)) history <- as_string(history)

  if (is_supported_terminal()) {
    ## This loads the history if needed
    ans <- .Call(
      "R_readline_read_line", prompt, multiline, history,
      completions
    )

  } else {

    if (!is.null(history)) {
      tmp <- tempfile()
      tryCatch(savehistory(tmp), error = function(e) e)
      on.exit(
        tryCatch(loadhistory(tmp), error = function(e) e),
        add = TRUE
      )
    }

    ans <- readline(prompt)

  }

  ## Save history if requested
  if (!is.null(history)) {
    cat(ans, sep = "", "\n", file = history, append = TRUE)
  }
  ans
}

is_supported_terminal <- function() {
  isatty(stdin()) &&
    .Platform$OS.type == "unix" &&
    Sys.getenv("RSTUDIO") != 1 &&
    Sys.getenv("R_GUI_APP_VERSION") == "" &&
    .Platform$GUI != "Rgui" &&
    !identical(getOption("STERM"), "iESS") && Sys.getenv("EMACS") != "t"
}
