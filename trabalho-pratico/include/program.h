/**
 * @file program.h
 * @brief Responsible for mantaining the program state.
 */

#ifndef PROGRAM_H
#define PROGRAM_H

#include "data/database.h"
#include "workers/batch.h"

/**
 * @brief Program state
 * @details Responsible for mantaining the program state.
 */
typedef struct Program Program;

/**
 * @brief Program mode
 * @details Program mode that the program is running on.
 */
typedef enum ProgramMode {
  PROGRAM_MODE_BATCH = 0,
  PROGRAM_MODE_INTERACTIVE = 1,
} ProgramMode;

/**
 * @brief Initializes the program state
 * @details Initializes the program.
 * @return Initialized program in the given program mode.
 */
Program *initialize_program(ProgramMode);

/**
 * @brief Executes the program
 * @details Executes the program with the given arguments.
 *
 * @param program Program.
 * @param args Arguments given to the program on startup.
 * @return 0 if the execution succeeded.
 */
int execute_program(Program *program, char **args);

/**
 * @brief Frees the program.
 * @details Frees the data used by the program.
 *
 * @param program Program.
 */
void free_program(Program *program);

#endif