/**
 * @file interactive.h
 * @brief Responsible for handling the interactive mode.
 */
#ifndef INTERACTIVE_H
#define INTERACTIVE_H

#include "io/graphics/terminal.h"
#include "program.h"

/**
 * @brief Interactive worker.
 * @details Responsible for handling the interactive mode.
 *
 * @param program Program.
 */
void interactive_worker(Program *program);

/**
 * @brief Interactive loop.
 * @details Interactive loop of the program.
 *
 * @param terminal Terminal.
 * @param program Program.
 * @return 0 if the execution succeeded.
 */
int app_loop(Terminal *terminal, Program *program);

/**
 * @brief Query selection screen.
 * @details Query selection screen.
 *
 * @param terminal Terminal.
 * @param database Database.
 * @param program Program.
 */
void querier_screen(Terminal *terminal, Database *database, Program *program);

/**
 * @brief Query result table.
 * @details Query result table with pagination.
 *
 * @param terminal Terminal.
 * @param database Database.
 * @param query_id Query id.
 * @param query_arguments Query arguments.
 */
void query_table(Terminal *terminal, Database *database, int query_id,
                 char *query_arguments);

/**
 * @brief Query main menu.
 * @details Query main menu.
 *
 * @param terminal Terminal.
 * @param database Database.
 *
 */
int main_menu(Terminal *terminal, char *dataset_path);

/**
 * @brief Loading screen.
 *
 * @param terminal Terminal.
 * @param text Text.
 *
 */
WINDOW *loading_screen(Terminal *terminal, char *text);

/**
 * @brief Show about menu.
 *
 * @param terminal Terminal.
 * @param window Window.
 *
 */
void show_about_menu(Terminal *terminal, WINDOW *window);

#endif