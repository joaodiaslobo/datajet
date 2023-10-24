#include <stdio.h>

#include "program.h"

int main(int argc, char** argv) {
  ProgramMode programMode;

  switch (argc) {
    case 3:
      programMode = PROGRAM_MODE_BATCH;
      break;
    case 1:
      programMode = PROGRAM_MODE_INTERACTIVE;
      break;
    default:
      printf("Wrong number of arguments given.\n");
      return -1;
  }

  Program* program = initialize_program(programMode);
  int result = execute_program(program, argv + 1);
  free_program(program);

  return result;
}