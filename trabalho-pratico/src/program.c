#include "program.h"

#include <stdio.h>
#include <stdlib.h>

struct Program {
  ProgramMode mode;
  Database *database;
};

Program *initialize_program(ProgramMode programMode) {
  Program *program = malloc(sizeof(Program));
  program->mode = programMode;
  /* TODO: Database needs to be initialized here in the future. */
  program->database = NULL;
  return program;
}

int execute_program(Program *program, char **args) {
  switch (program->mode) {
    case PROGRAM_MODE_BATCH:
      batch_worker(args);
      break;
    case PROGRAM_MODE_INTERACTIVE:
      printf("Interactive mode hasn't been implemented yet.\n");
      break;
    default:
      break;
  }
  return 0;
}