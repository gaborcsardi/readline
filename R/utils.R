

as_string <- function(x) {
  x <- as.character(x)
  if (length(x) != 1 || is.na(x)) stop("`x' must be a character string")
  x
}
