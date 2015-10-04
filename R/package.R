
#' @export
#' @useDynLib linenoise R_linenoise_read_line

read_line <- function(prompt = "") {
  prompt <- as_string(prompt)
  .Call("R_linenoise_read_line", prompt)
}


#' @export

save_input_history <- function(file = "") {
  TODO
}


#' @export

load_input_history <- function(file = "") {
  TODO
}
