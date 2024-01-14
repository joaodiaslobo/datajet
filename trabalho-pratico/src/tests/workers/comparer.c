#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io/file.h"

#define BUFFER_SIZE 1024

/*
 * Compares two files line by line.
 * Returns the first line where the files differ.
 * Returns -1 if the files are equal.
 */
static int file_compare(char *file1_path, char *file2_path) {
  FILE *file1 = open_file(file1_path);
  FILE *file2 = open_file(file2_path);

  if (file1 == NULL || file2 == NULL) {
    return -1;
  }

  char file1_line[BUFFER_SIZE] = "";
  char file2_line[BUFFER_SIZE] = "";

  int line = 0;
  while (fgets(file1_line, BUFFER_SIZE, file1) != NULL &&
         fgets(file2_line, BUFFER_SIZE, file2) != NULL) {
    if (strcmp(file1_line, file2_line) != 0) {
      close_file(file1);
      close_file(file2);

      return line;
    }
    line++;
  }

  close_file(file1);
  close_file(file2);
  return -1;
}