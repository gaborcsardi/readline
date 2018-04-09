
#' Low level interface for replxx
#'
#'
#' @export

replxx <- function() {
  .Call(C_rreplxx_new)
}

#' @export
#' @rdname replxx

replxx_set_highlighter <- function(replxx, fun) {
  stopifnot(is.function(fun))
  stopifnot(inherits(replxx, "replxx"))
  .Call(C_rreplxx_set_highlighter, replxx, fun)
}

#' @export
#' @rdname replxx

replxx_set_completion <- function(replxx, fun) {
  stopifnot(is.function(fun))
  stopifnot(inherits(replxx, "replxx"))
  .Call(C_rreplxx_set_completion, replxx, fun)
}

#' @export
#' @rdname replxx

replxx_add_completions <- function(completions, strings) {
  strings <- as.character(strings)
  stopifnot(inherits(completions, "replxx_completions"))
  .Call(C_rreplxx_add_completions, completions, strings)
}

#' @export
#' @rdname replxx

replxx_set_hinter <- function(replxx, fun) {
  stopifnot(is.function(fun))
  stopifnot(inherits(replxx, "replxx"))
  .Call(C_rreplxx_set_hinter, replxx, fun)
}

#' @export
#' @rdname replxx

replxx_add_hints <- function(hints, strings) {
  strings <- as.character(strings)
  stopifnot(inherits(hints, "replxx_hints"))
  .Call(C_rreplxx_add_hints, hints, strings)
}

#' @export
#' @rdname replxx

replxx_input <- function(replxx, prompt = "? ") {
  prompt <- as_string(prompt)
  stopifnot(inherits(replxx, "replxx"))
  .Call(C_rreplxx_input, replxx, prompt)
}

#' @export
#' @rdname replxx

replxx_print <- function(replxx, fmt, ...) {
  fmt <- as_string(fmt)
  args <- unlist(lapply(list(...),  as_string))
  stopifnot(inherits(replxx, "replxx"))
  .Call(C_rreplxx_print, replxx, fmt, args)
}

#' @export
#' @rdname replxx

replxx_set_preload <- function(replxx, text) {
  text <-  as_string(text)
  stopifnot(inherits(replxx, "replxx"))
  .Call(C_rreplxx_set_preload, replxx, text)
}

#' @export
#' @rdname replxx

replxx_history_add <- function(replxx, lines) {
  lines <- as.character(lines)
  stopifnot(inherits(replxx, "replxx"))
  .Call(C_rreplxx_history_add, replxx, lines)
}

#' @export
#' @rdname replxx

replxx_history_size <- function(replxx) {
  stopifnot(inherits(replxx, "replxx"))
  .Call(C_rreplxx_history_size, replxx)
}

#' @export
#' @rdname replxx

replxx_set_word_break_characters <- function(replxx, chars) {
  stopifnot(inherits(replxx, "replxx"))
  chars <- paste(as.character(chars), collapse = "")
  .Call(C_rreplxx_set_word_break_characters, replxx, chars)
}

#' @export
#' @rdname replxx

replxx_set_special_prefixes <- function(replxx, specials) {
  stopifnot(inherits(replxx, "replxx"))
  specials <- paste(as.character(specials), collapse = "")
  .Call(C_rreplxx_set_special_prefixes, replxx, specials)
}

#' @export
#' @rdname replxx

replxx_set_max_line_size <- function(replxx, len) {
  stopifnot(inherits(replxx, "replxx"))
  len <- as_count(len)
  .Call(C_rreplxx_set_max_line_size, replxx, len)
}

#' @export
#' @rdname replxx

replxx_set_max_hint_rows <- function(replxx, count) {
  stopifnot(inherits(replxx, "replxx"))
  count <- as_count(count)
  .Call(C_rreplxx_set_max_max_hint_rows, replxx, count)
}

#' @export
#' @rdname replxx

replxx_set_double_tab_completion <- function(replxx, on) {
  stopifnot(inherits(replxx, "replxx"))
  on <- as_flag(on)
  .Call(C_rreplxx_set_double_tab_completion, replxx, on)
}

#' @export
#' @rdname replxx

replxx_set_complete_on_empty <- function(replxx, on) {
  stopifnot(inherits(replxx, "replxx"))
  on <- as_flag(on)
  .Call(C_rreplxx_set_complete_on_empty, replxx, on)
}

#' @export
#' @rdname replxx

replxx_set_beep_on_ambiguous_completion <- function(replxx, on) {
  stopifnot(inherits(replxx, "replxx"))
  on <- as_flag(on)
  .Call(C_rreplxx_set_beep_on_ambiguous_completion, replxx, on)
}

#' @export
#' @rdname replxx

replxx_set_no_color <- function(replxx, on) {
  stopifnot(inherits(replxx, "replxx"))
  on <- as_flag(on)
  .Call(C_rreplxx_set_no_color, replxx, on)
}

#' @export
#' @rdname replxx

replxx_set_max_history_size <- function(replxx, len) {
  stopifnot(inherits(replxx, "replxx"))
  len <- as_count(len)
  .Call(C_rreplxx_set_max_history_size, replxx, len)
}

#' @export
#' @rdname replxx

replxx_get_history_line <- function(replxx, index) {
  stopifnot(inherits(replxx, "replxx"))
  index <- as_count(index)
  .Call(C_rreplxx_get_history_line, replxx, index)
}

#' @export
#' @rdname replxx

replxx_save_history <-  function(replxx, path) {
  stopifnot(inherits(replxx, "replxx"))
  path <- as_string(path)
  .Call(C_rreplxx_save_history, replxx, path)
}

#' @export
#' @rdname replxx

replxx_load_history <- function(replxx, path) {
  stopifnot(inherits(replxx, "replxx"))
  path <- as_string(path)
  .Call(C_rreplxx_load_history, replxx, path)
}

#' @export
#' @rdname replxx

replxx_clear_screen <- function(replxx) {
  stopifnot(inherits(replxx, "replxx"))
  .Call(C_rreplxx_clear_screen, replxx)
}
