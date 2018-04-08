
#' Read a line from the terminal
#'
#' @param prompt A string that is printed at the beginning of the
#'   line of the user input. Ideally it should be short, so there
#'   is enough space for the input. It can be colored and styled
#'   with ANSI escape sequences from the \code{crayon} package.
#' @param default Default value.
#' @param history If not \code{NULL}, then it must be a character
#'   scalar, the name of the file that is used as a browseable history. The
#'   newly entered entry is added to this file. Note that history
#'   might not be supported by the \code{base::readline} fallback
#'   method.
#' @param completions A character vector of possible TAB-completions or
#'   hints.
#' @param show_hints Whether to show hints.
#' @param tab_complete Whether to activate TAB completion.
#' @return A character scalar, the string that was read.
#'
#' @export
#' @useDynLib lines, .registration = TRUE, .fixes = "C_"
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
#'   read_line(prompt = "what> ", completions = c("foobar", "foo", "bar"),
#'             tab_complete = TRUE, show_hints = FALSE)
#' }

read_line <- function(prompt = "? ", default = "", history = NULL,
                      completions = character(), show_hints = TRUE,
                      tab_complete = FALSE) {

  default <- as_string(default)
  if (!is.null(history)) history <- as_string(history)
  completions <- as.character(completions)
  show_hints <- as_flag(show_hints)
  tab_complete <- as_flag(tab_complete)

  res <- tryCatch(
    .Call(C_read_line, prompt, default, history, completions, show_hints,
          tab_complete),
    interrupt = function(e) stop("Interrupted")
  )
  if (is.null(res)) stop("Interrupted")
  res
}
