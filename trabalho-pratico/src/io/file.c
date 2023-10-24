#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *open_file(char *path) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    // TODO: Handle error.
  }

  return file;
}

void close_file(FILE *file) { fclose(file); }

char *build_full_file_path(char *folder, char *file_name) {
  char *path = malloc(sizeof(char) * (strlen(folder) + strlen(file_name) + 1));
  strcpy(path, folder);
  strcat(path, file_name);

  return path;
}