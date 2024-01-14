#include <stdio.h>
#include <stdlib.h>

typedef enum Color {
  DEFAULT = 0,
  BLACK = 30,
  RED = 31,
  GREEN = 32,
  YELLOW = 33,
  BLUE = 34,
  MAGENTA = 35,
  CYAN = 36
} Color;

typedef enum Style { REGULAR = 0, BOLD = 1 } Style;

/*
 * Reimplementation of printf from C standard library that allows for color
 * printing.
 */
__fortify_function int print(const char *__restrict __fmt, Color color,
                             Style style, ...) {
  printf("\033[%d;%dm", style, color);
  return __printf_chk(__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack());
}