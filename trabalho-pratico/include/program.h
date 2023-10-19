#ifndef PROGRAM_H
#define PROGRAM_H

#include "data/database.h"
#include "workers/batch.h"

typedef struct Program Program;

typedef enum ProgramMode {
  PROGRAM_MODE_BATCH = 0,
  PROGRAM_MODE_INTERACTIVE = 1,
} ProgramMode;

Program *initialize_program(ProgramMode);

int execute_program(Program *program, char **args);

#endif