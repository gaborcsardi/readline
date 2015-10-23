

ansi_regex <- paste0("(?:(?:\\x{001b}\\[)|\\x{009b})",
                     "(?:(?:[0-9]{1,3})?(?:(?:;[0-9]{0,3})*)?[A-M|f-m])",
                     "|\\x{001b}[A-M]")


strip_ansi <- function(string) gsub(ansi_regex, "", string, perl = TRUE)

#' Read a line from the terminal
#'
#' @param prompt A string that is printed at the beginning of the
#'   line of the user input. Ideally it should be short, so there
#'   is enough space for the input. It can be colored and styled
#'   with ANSI escape sequences from the \code{crayon} package.
#' @return A character scalar, the string that was read.
#'
#' @export
#' @useDynLib readline R_readline_read_line

read_line <- function(prompt = "") {
  prompt <- as_string(prompt)
  if (is_supported_terminal()) {
    .Call("R_readline_read_line", prompt, strip_ansi(prompt))
  } else {
    readline(prompt)
  }
}


save_input_history <- function(file = "") {
  ## TODO
}


load_input_history <- function(file = "") {
  ## TODO
}

is_supported_terminal <- function() {
  isatty(stdin()) &&
    Sys.getenv("RSTUDIO") != 1 &&
    Sys.getenv("R_GUI_APP_VERSION") == "" &&
    .Platform$GUI != "Rgui" &&
    !identical(getOption("STERM"), "iESS") && Sys.getenv("EMACS") != "t"
}
