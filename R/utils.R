

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
