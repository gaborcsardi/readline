

ansi_regex <- paste0("(?:(?:\\x{001b}\\[)|\\x{009b})",
                     "(?:(?:[0-9]{1,3})?(?:(?:;[0-9]{0,3})*)?[A-M|f-m])",
                     "|\\x{001b}[A-M]")


strip_ansi <- function(string) gsub(ansi_regex, "", string, perl = TRUE)


#' @export
#' @useDynLib linenoise R_linenoise_read_line

read_line <- function(prompt = "") {
  prompt <- as_string(prompt)
  .Call("R_linenoise_read_line", prompt, strip_ansi(prompt))
}


#' @export

save_input_history <- function(file = "") {
  TODO
}


#' @export

load_input_history <- function(file = "") {
  TODO
}
