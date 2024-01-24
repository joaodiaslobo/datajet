#include "program.h"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "data/database.h"
#include "workers/interactive.h"

struct Program {
  ProgramMode mode;
  Database *database;
};

Program *initialize_program(ProgramMode programMode) {
  Program *program = malloc(sizeof(Program));
  program->mode = programMode;
  program->database = initialize_database();

  setlocale(LC_ALL, "");
  setlocale(LC_COLLATE, "en_US.UTF-8");

  return program;
}

void refresh_database(Program *program) {
  free_database(program->database);
  program->database = initialize_database();
}

void free_program(Program *program) {
  free_database(program->database);
  free(program);
}

Database *program_get_database(Program *program) { return program->database; }

int execute_program(Program *program, char **args) {
  switch (program->mode) {
    case PROGRAM_MODE_BATCH:
      batch_worker(args, program->database);
      break;
    case PROGRAM_MODE_INTERACTIVE:
      interactive_worker(program);
      break;
    default:
      break;
  }
  return 0;
}