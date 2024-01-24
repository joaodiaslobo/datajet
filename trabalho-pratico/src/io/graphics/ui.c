#include "io/graphics/ui.h"

#include <ncurses.h>
#include <string.h>

int count_newlines(char text[]);

int menu_select(int options, char *texts[], int width, int y, int x) {
  int selection = 0, key = 0;
  int lines = options + 4;

  WINDOW *selectWindow = newwin(lines, width, y, x);
  box(selectWindow, 0, 0);
  refresh();
  wrefresh(selectWindow);
  keypad(selectWindow, true);

  while (key != 10) {
    for (int i = 0; i < options; i++) {
      if (i == selection) {
        wattron(selectWindow, COLOR_PAIR(2));
        mvwprintw(selectWindow, i + 2, 4, "[x] %s", texts[i]);
        wattroff(selectWindow, COLOR_PAIR(2));
      } else {
        mvwprintw(selectWindow, i + 2, 4, "[ ] %s", texts[i]);
      }
      wrefresh(selectWindow);
    }

    move(0, 0);

    key = wgetch(selectWindow);
    switch (key) {
      case KEY_UP:
        if (selection > 0) {
          selection--;
        } else {
          selection = options - 1;
        }
        break;
      case KEY_DOWN:
        if (selection < options - 1) {
          selection++;
        } else {
          selection = 0;
        }
        break;
      default:
        break;
    }
  }

  wclear(selectWindow);
  wrefresh(selectWindow);
  delwin(selectWindow);
  return selection;
}

void modal_ok(char text[], int width, int screenYMax, int screenXMax) {
  int key = 0;
  int necessaryLines = count_newlines(text) + 1 + 4;
  int posY = (screenYMax - necessaryLines) / 2;
  int posX = (screenXMax - width) / 2;

  WINDOW *modalWindow = newwin(necessaryLines, width, posY, posX);
  box(modalWindow, 0, 0);
  refresh();
  wrefresh(modalWindow);
  keypad(modalWindow, true);

  mvwprintw(modalWindow, 1, 2, "%s", text);

  wattron(modalWindow, COLOR_PAIR(2));
  mvwprintw(modalWindow, necessaryLines - 2, width - 4, "OK");
  wattroff(modalWindow, COLOR_PAIR(2));

  while (key != 10) {
    key = wgetch(modalWindow);
  }

  wclear(modalWindow);
  wrefresh(modalWindow);
  delwin(modalWindow);
}

int modal_confim(char text[], int width, int screenYMax, int screenXMax,
                 char no[], char yes[]) {
  int key = 0, option = 0;
  int necessaryLines = count_newlines(text) + 1 + 4;
  int posY = (screenYMax - necessaryLines) / 2;
  int posX = (screenXMax - width) / 2;

  WINDOW *modalWindow = newwin(necessaryLines, width, posY, posX);
  box(modalWindow, 0, 0);
  refresh();
  wrefresh(modalWindow);
  keypad(modalWindow, true);

  mvwprintw(modalWindow, 1, 2, "%s", text);

  while (key != 10) {
    if (!option) {
      wattron(modalWindow, COLOR_PAIR(2));
      mvwprintw(modalWindow, necessaryLines - 2, 2, "%s", yes);
      wattroff(modalWindow, COLOR_PAIR(2));
      mvwprintw(modalWindow, necessaryLines - 2, width - 4, "%s", no);
    } else {
      wattron(modalWindow, COLOR_PAIR(2));
      mvwprintw(modalWindow, necessaryLines - 2, width - 4, "%s", no);
      wattroff(modalWindow, COLOR_PAIR(2));
      mvwprintw(modalWindow, necessaryLines - 2, 2, "%s", yes);
    }

    key = wgetch(modalWindow);
    switch (key) {
      case KEY_RIGHT:
        if (option) {
          option--;
        } else {
          option++;
        }
        break;
      case KEY_LEFT:
        if (option) {
          option--;
        } else {
          option++;
        }
        break;
      default:
        break;
    }
  }

  wclear(modalWindow);
  wrefresh(modalWindow);
  delwin(modalWindow);
  return !option;
}

void text_input_box(Vector2D pos, int width, int inputSize, char *text,
                    char *input) {
  WINDOW *input_window = newwin(5, width, pos.y, pos.x);
  box(input_window, 0, 0);
  refresh();
  wrefresh(input_window);

  wattron(input_window, COLOR_PAIR(2));
  mvwprintw(input_window, 0, 2, "%s", text);
  wattroff(input_window, COLOR_PAIR(2));
  mvwaddch(input_window, 3, 1, '>');

  int cursor = 0;
  int ch;

  wmove(input_window, 3, 3);
  curs_set(1);

  while ((ch = wgetch(input_window)) != '\n' && cursor < inputSize - 1) {
    if (ch == KEY_BACKSPACE || ch == 127) {
      if (cursor > 0) {
        cursor--;
        input[cursor] = ' ';
        mvwprintw(input_window, 3, 3, "%s", input);
        input[cursor] = '\0';
        wmove(input_window, 3, 3 + cursor);
        wrefresh(input_window);
      }
    } else {
      input[cursor] = ch;
      input[cursor + 1] = '\0';
      mvwprintw(input_window, 3, 3, "%s", input);
      cursor++;
      wmove(input_window, 3, 3 + cursor);
      wrefresh(input_window);
    }
  }

  curs_set(0);

  wclear(input_window);
  wrefresh(input_window);
  delwin(input_window);
}

void draw_ascii_art_to_screen(WINDOW *window, Vector2D pos, char *file_path) {
  FILE *file = fopen(file_path, "r");
  char line[100];
  int line_count = 0;

  while (fgets(line, 100, file) != NULL) {
    mvwprintw(window, pos.y + line_count, pos.x, "%s", line);
    line_count++;
  }

  fclose(file);
}

int count_newlines(char text[]) {
  int count = 0;
  for (int i = 0; text[i] != '\0'; i++) {
    if (text[i] == '\n') {
      count++;
    }
  }
  return count;
}