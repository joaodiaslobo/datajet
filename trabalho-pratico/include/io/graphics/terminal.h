/**
 * @file terminal.h
 * @brief Responsible for handling the terminal.
 */
#ifndef TERMINAL_H
#define TERMINAL_H

#include <ncurses.h>

typedef struct terminal Terminal;

/**
 * @brief Initializes the terminal.
 * @details Initializes the terminal.
 *
 * @param window Window of the terminal.
 * @return Initialized terminal.
 */
Terminal *initialize_terminal(WINDOW *window);

/**
 * @brief Gets the terminal window.
 * @details Gets the terminal window.
 *
 * @param terminal Terminal.
 * @return Terminal window.
 */
int get_terminal_width(Terminal *terminal);

/**
 * @brief Gets the terminal window.
 * @details Gets the terminal window.
 *
 * @param terminal Terminal.
 * @return Terminal window.
 */
int get_terminal_height(Terminal *terminal);

#endif