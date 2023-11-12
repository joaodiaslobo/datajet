#include "io/file.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_BUFFER_SIZE 1024

struct fileBuffer {
  char *name;
  char *content;
  int content_size;
  int size;
};

FILE *open_file(char *path) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    // TODO: Handle error.
  }

  return file;
}

void close_file(FILE *file) { fclose(file); }

char *build_full_file_path(char *folder, char *file_name) {
  char *path = malloc(sizeof(char) * (strlen(folder) + strlen(file_name) + 2));
  strcpy(path, folder);
  strcat(path, "/");
  strcat(path, file_name);

  return path;
}

FileBuffer *initialize_file_buffer(char *name) {
  FileBuffer *buffer = malloc(sizeof(FileBuffer));

  buffer->name = name;
  buffer->content = malloc(sizeof(char) * DEFAULT_BUFFER_SIZE);
  buffer->content[0] = '\0';
  buffer->content_size = 0;
  buffer->size = DEFAULT_BUFFER_SIZE;

  return buffer;
}

void free_file_buffer(FileBuffer *buffer) {
  free(buffer->content);
  free(buffer);
}

void append_to_file_buffer(FileBuffer *buffer, char *content) {
  int content_size = strlen(content);
  int new_size = buffer->content_size + content_size;

  while (new_size > buffer->size) {
    buffer->size *= 2;
    buffer->content = realloc(buffer->content, buffer->size);
  }

  strcat(buffer->content, content);
  buffer->content_size = new_size;
}

void write_file_buffer(FileBuffer *buffer) {
  FILE *destination_file = fopen(buffer->name, "w");
  fprintf(destination_file, "%s", buffer->content);
  fclose(destination_file);
}

void create_directory_if_doesnt_exist(char *path) {
  g_mkdir_with_parents(path, 0700);
}