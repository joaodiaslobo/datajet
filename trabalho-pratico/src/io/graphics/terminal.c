#include "io/graphics/terminal.h"

#include <ncurses.h>
#include <stdlib.h>

struct terminal {
  int y_max;
  int x_max;
  WINDOW *main_window;
};

Terminal *initialize_terminal(WINDOW *window) {
  Terminal *terminal = malloc(sizeof(Terminal));
  terminal->main_window = window;
  getmaxyx(window, terminal->y_max, terminal->x_max);
  return terminal;
}

int get_terminal_width(Terminal *terminal) { return terminal->x_max; }

int get_terminal_height(Terminal *terminal) { return terminal->y_max; }