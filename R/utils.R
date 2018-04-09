

as_string <- function(x) {
  x <- as.character(x)
  if (length(x) != 1 || is.na(x)) stop("`x' must be a character string")
  x
}


as_flag <- function(x) {
  x <- as.logical(x)
  if (length(x) != 1 || is.na(x)) stop("`x' must be a logical flag")
  x
}

as_count <- function(x) {
  if (! is.numeric(x) || length(x) != 1 || is.na(x) || as.integer(x) != x ||
      x <= 0) {
    stop("`x' must be count (positive integer scalar)")
  }
  as.integer(x)
}
