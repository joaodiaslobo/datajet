#include "workers/interactive.h"

#include <ncurses.h>
#include <stdlib.h>

#include "data/database.h"
#include "data/queries.h"
#include "io/graphics/terminal.h"
#include "io/graphics/ui.h"
#include "io/writing/writer.h"
#include "program.h"
#include "utils/utilities.h"

void interactive_worker(Program *program) {
  WINDOW *window = initscr();
  curs_set(0);
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  meta(stdscr, TRUE);
  keypad(stdscr, TRUE);
  mousemask(BUTTON1_CLICKED | BUTTON3_CLICKED, NULL);
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  wbkgd(window, COLOR_PAIR(1));
  intrflush(window, FALSE);

  // For titles
  init_pair(2, COLOR_WHITE, COLOR_BLUE);

  Terminal *terminal = initialize_terminal(window);

  while (1) {
    // Main window background
    draw_ascii_art_to_screen(window,
                             (Vector2D){get_terminal_width(terminal) / 2 - 20,
                                        get_terminal_height(terminal) / 2 - 10},
                             "assets/logo.art");
    box(window, 0, 0);
    wattron(window, COLOR_PAIR(2));
    mvwaddstr(window, 0, 2, "DataJet - v1.0");
    wattroff(window, COLOR_PAIR(2));
    wrefresh(window);
    wrefresh(window);

    int exec = app_loop(terminal, program);
    if (exec == -1) break;
  }

  endwin();
}

int app_loop(Terminal *terminal, Program *program) {
  char *dataset_path = malloc(sizeof(char) * 20);
  int mode = main_menu(terminal, dataset_path);

  switch (mode) {
    case 0: {
      WINDOW *loading = loading_screen(terminal, "LOADING DATASET");
      csv_populate_database(program_get_database(program), dataset_path);
      wclear(loading);
      wrefresh(loading);
      delwin(loading);
      refresh();
      free(dataset_path);
      querier_screen(terminal, program_get_database(program), program);
    }
      return 0;
      break;
    case 1:
      return 1;
    default:
      return -1;
      break;
  }
}

void querier_screen(Terminal *terminal, Database *database, Program *program) {
  while (1) {
    char *query = malloc(sizeof(char) * 20);
    query[0] = '\0';

    int shoud_exit = 0;
    while (1) {
      Vector2D pos = {get_terminal_width(terminal) / 2 - 15,
                      get_terminal_height(terminal) / 2};
      text_input_box(pos, 30, 20, "Query ID (1 - 10):", query);
      if (!(parse_number(query) > 0 && parse_number(query) <= 10)) {
        int ans = modal_confim(
            "Invalid query ID. Please choose a number between 1 and 10.", 63,
            get_terminal_height(terminal), get_terminal_width(terminal), "OK",
            "EXIT");
        if (ans == 0) {
          continue;
        } else {
          shoud_exit = 1;
          break;
        }
      } else {
        break;
      }
    }

    if (shoud_exit) {
      free(query);
      refresh_database(program);
      return;
    }

    int query_id = parse_number(query);
    int args = -1;
    Vector2D pos = {get_terminal_width(terminal) / 2 - 25,
                    get_terminal_height(terminal) / 2 - 5};
    WINDOW *outter = newwin(12, 52, pos.y - 1, pos.x - 1);
    WINDOW *window = newwin(10, 50, pos.y, pos.x);
    char *query_arguments = malloc(sizeof(char) * 20);
    query_arguments[0] = '\0';
    while (1) {
      box(outter, 0, 0);
      wrefresh(outter);
      wrefresh(window);
      wattron(outter, COLOR_PAIR(2));
      mvwaddstr(outter, 0, 2, query_definitions[query_id - 1].name);
      wattroff(outter, COLOR_PAIR(2));
      mvwaddstr(window, 1, 1, query_definitions[query_id - 1].description);
      wrefresh(outter);
      wrefresh(window);
      Vector2D pos2 = {get_terminal_width(terminal) / 2 - 20,
                       get_terminal_height(terminal) / 2};

      text_input_box(pos2, 40, 20, "Query arguments:", query_arguments);
      args = count_spaces(query_arguments) + 1;
      if (!(args >= query_definitions[query_id - 1].min_args &&
            args <= query_definitions[query_id - 1].max_args)) {
        modal_ok("Invalid number of arguments. Please try again.", 60,
                 get_terminal_height(terminal), get_terminal_width(terminal));
      } else {
        break;
      }
    }

    wclear(outter);
    wrefresh(outter);
    delwin(outter);
    wclear(window);
    wrefresh(window);
    delwin(window);

    query_table(terminal, database, query_id, query_arguments);
    free(query);
    clear();
    refresh();
  }
}

void query_table(Terminal *terminal, Database *database, int query_id,
                 char *query_arguments) {
  WINDOW *window = newwin(
      get_terminal_height(terminal) - 2, get_terminal_width(terminal) / 1.2, 1,
      get_terminal_width(terminal) - get_terminal_width(terminal) / 1.2 - 1);
  wrefresh(window);

  box(window, 0, 0);
  RowWriter *writer = initialize_row_writer("temp", WRITE_MODE_INTERACTIVE);
  execute_query_and_save_result(writer, database, query_id - 1,
                                query_arguments);

  int fields = row_writer_get_number_of_fields(writer);

  int col_width = get_terminal_width(terminal) / 1.2 / fields;

  int current_page = 1;
  int items_per_page = get_terminal_height(terminal) - 6;
  int total_pages = row_writer_get_number_of_rows(writer) / items_per_page + 1;

  keypad(window, TRUE);

  wrefresh(window);

  row_writer_write_buffer(writer);

  while (1) {
    box(window, 0, 0);
    wrefresh(window);
    // Print field names
    for (int i = 0; i < fields; i++) {
      wattron(window, COLOR_PAIR(2));
      mvwprintw(window, 1, i * col_width + 1, "%s",
                row_writer_get_field_name(writer, i));
      wattroff(window, COLOR_PAIR(2));
      wrefresh(window);
    }
    // Print query result rows
    FILE *file = fopen("temp", "r");
    if (file != NULL) {
      int count = 0;
      char line[256];
      while (fgets(line, sizeof line, file) != NULL) {
        if (count >= items_per_page * (current_page - 1) &&
            count < items_per_page * current_page) {
          char *token = strtok(line, ";");
          for (int i = 0; i < fields && token != NULL; i++) {
            mvwprintw(window, 2 + count % items_per_page, i * col_width + 1,
                      "%s", token);
            box(window, 0, 0);
            wrefresh(window);
            token = strtok(NULL, ";");
          }
        } else {
          if (count >= items_per_page * current_page) break;
        }
        count++;
      }
      fclose(file);
    }
    box(window, 0, 0);
    wrefresh(window);

    // Print pages
    wattron(window, COLOR_PAIR(2));
    mvwprintw(window, get_terminal_height(terminal) - 4,
              get_terminal_width(terminal) / 1.2 - 9, "%d", current_page);
    wattroff(window, COLOR_PAIR(2));
    mvwprintw(window, get_terminal_height(terminal) - 4,
              get_terminal_width(terminal) / 1.2 - 6, "> %d", total_pages);
    mvwprintw(window, get_terminal_height(terminal) - 4,
              get_terminal_width(terminal) / 1.2 - 14, "1 <");
    wrefresh(window);

    // Print back
    mvwprintw(window, get_terminal_height(terminal) - 4, 1, "< [B]ack");
    wrefresh(window);

    int c = wgetch(window);

    switch (c) {
      case KEY_RIGHT:
        if (current_page < total_pages) current_page++;
        break;
      case KEY_LEFT:
        if (current_page > 1) current_page--;
        break;
      case 'b':
        remove("temp");
        return;
        break;
      default:
        break;
    }
    wclear(window);
  }

  wclear(window);
  wrefresh(window);
  delwin(window);
}

int main_menu(Terminal *terminal, char *dataset_path) {
  int selection = menu_select(3, (char *[]){"Load Dataset", "About", "Exit"},
                              30, get_terminal_height(terminal) / 2 - 5, 10);

  if (selection == 0) {
    Vector2D pos = {get_terminal_width(terminal) / 2 - 15,
                    get_terminal_height(terminal) / 2};
    clear();
    box(stdscr, 0, 0);
    wattron(stdscr, COLOR_PAIR(2));
    mvwaddstr(stdscr, 0, 2, "DataJet - v1.0");
    wattroff(stdscr, COLOR_PAIR(2));
    refresh();
    while (1) {
      text_input_box(pos, 30, 20, "Dataset path:", dataset_path);
      GDir *dir = g_dir_open(dataset_path, 0, NULL);
      if (dir != NULL) {
        g_dir_close(dir);
        break;
      } else {
        modal_ok("Invalid dataset directory. Please choose another path.", 60,
                 get_terminal_height(terminal), get_terminal_width(terminal));
      }
    }
    refresh();
  } else if (selection == 1) {
    clear();
    box(stdscr, 0, 0);
    wattron(stdscr, COLOR_PAIR(2));
    mvwaddstr(stdscr, 0, 2, "DataJet - v1.0");
    wattroff(stdscr, COLOR_PAIR(2));
    refresh();
    show_about_menu(terminal, stdscr);
  }

  return selection;
}

WINDOW *loading_screen(Terminal *terminal, char *text) {
  int width = 22;
  int height = 5;
  int x = get_terminal_width(terminal) / 2 - width / 2;
  int y = get_terminal_height(terminal) / 2 - height / 2;

  WINDOW *window = newwin(height, width, y, x);
  box(window, 0, 0);
  refresh();
  wrefresh(window);
  mvwprintw(window, 2, 2, "%s", text);
  wattron(window, A_BLINK | A_BOLD);
  mvwprintw(window, 2, 2 + strlen(text), "...");
  wattroff(window, A_BLINK | A_BOLD);
  wrefresh(window);

  return 0;
}

void show_about_menu(Terminal *terminal, WINDOW *window) {
  int key = 0;
  while (key != 10) {
    wattron(window, A_BOLD);
    mvwprintw(window, get_terminal_height(terminal) / 5,
              get_terminal_width(terminal) / 2, "ABOUT");
    wattroff(window, A_BOLD);

    wattron(window, A_NORMAL);
    mvwprintw(window, get_terminal_height(terminal) / 4 + 4,
              get_terminal_width(terminal) / 2 - 103 / 2 + 1,
              "This program was developed by Hélder Gomes (A104100), João Lobo "
              "(A104356) and Rita Camacho (A104439)");
    mvwprintw(window, get_terminal_height(terminal) / 4 + 5,
              get_terminal_width(terminal) / 2 - 102 / 2 + 1,
              "Software Engineering & Computer Science students at University "
              "of Minho, as part of the final project");
    mvwprintw(window, get_terminal_height(terminal) / 4 + 6,
              get_terminal_width(terminal) / 2 - 91 / 2 + 1,
              "of the course \"Computer Labs III\" of the 2nd year (1st "
              "semester, academic year 2023/2024).");
    mvwprintw(window, get_terminal_height(terminal) / 4 + 7,
              get_terminal_width(terminal) / 2 - 92 / 2 + 1,
              "For further details, visit the \"DataJet\" repository, "
              "published on GitHub, and our profiles:");
    mvwprintw(window, get_terminal_height(terminal) / 4 + 10,
              get_terminal_width(terminal) / 2 - 38 / 2 + 1,
              "@helderrrg @joaodiaslobo @ritacamacho");
    wattroff(window, A_NORMAL);

    wattron(window, A_BOLD);
    mvwprintw(window, get_terminal_height(terminal) - 5,
              get_terminal_width(terminal) / 2 - 23 / 2 + 2,
              "Press [ENTER] to leave");
    wattroff(window, A_BOLD);

    key = wgetch(window);
  }
  clear();
}