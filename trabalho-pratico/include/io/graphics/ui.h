/**
 * @file ui.h
 * @brief Responsible for handling the user interface.
 */
#ifndef UI_H
#define UI_H

#include <ncurses.h>

typedef struct vector2D {
  int x;
  int y;
} Vector2D;

/*
 * @brief Select menu.
 * @details Initializes the user interface.
 *
 * @param options Number of options.
 * @param texts Texts of the options.
 * @param width Width of the menu.
 * @param y Y position of the menu.
 * @param x X position of the menu.
 * @return Selected option.
 */
int menu_select(int options, char *texts[], int width, int y, int x);

/**
 * @brief Modal.
 * @details Initializes a modal with the given text.
 *
 * @param text Text of the modal.
 * @param width Width of the modal.
 * @param screenYMax Maximum Y position of the screen.
 * @param screenXMax Maximum X position of the screen.
 */
void modal_ok(char text[], int width, int screenYMax, int screenXMax);

/**
 * @brief Modal.
 * @details Initializes a modal with the given text and options.
 *
 * @param text Text of the modal.
 * @param width Width of the modal.
 * @param screenYMax Maximum Y position of the screen.
 * @param screenXMax Maximum X position of the screen.
 * @param no Text of the no option.
 * @param yes Text of the yes option.
 * @return 1 if the yes option was selected, 0 otherwise.
 */
int modal_confim(char text[], int width, int screenYMax, int screenXMax,
                 char no[], char yes[]);

/**
 * @brief Text input box.
 * @details Initializes a text input box with the given text and input.
 *
 * @param pos Position of the text input box.
 * @param width Width of the text input box.
 * @param inputSize Size of the input.
 * @param text Text of the text input box.
 * @param input Input of the text input box.
 */
void text_input_box(Vector2D pos, int width, int inputSize, char *text,
                    char *input);

/**
 * @brief Draws ASCII art to screen.
 * @details Draws ASCII art to screen.
 *
 * @param window Window to draw to.
 * @param pos Position of the ASCII art.
 * @param file_path Path of the ASCII art file.
 */
void draw_ascii_art_to_screen(WINDOW *window, Vector2D pos, char *file_path);

#endif