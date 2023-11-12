#include "io/writing/writer.h"

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "io/file.h"

#define BUFFER_SIZE 1024
#define VALUE_BUFFER_SIZE 128

struct rowWriter {
  void (*EntityLineWriter)(RowWriter *, va_list);
  char **field_names;
  char **format;
  int row;
  FileBuffer *buffer;
  WriteMode mode;
};

RowWriter *initialize_row_writer(char *file_name, WriteMode writeMode) {
  RowWriter *writer = malloc(sizeof(RowWriter));
  writer->field_names = NULL;
  writer->format = NULL;
  writer->row = 0;
  writer->buffer = initialize_file_buffer(file_name);
  writer->mode = writeMode;
  return writer;
}

void row_writer_set_field_names(RowWriter *writer, char **field_names) {
  writer->field_names = field_names;
}

void row_writer_set_formatting(RowWriter *writer, char **formatting) {
  writer->format = formatting;
}

void free_and_finish_writing_row(RowWriter *writer) {
  write_file_buffer(writer->buffer);
  free_row_writer(writer);
}

void free_row_writer(RowWriter *writer) {
  free_file_buffer(writer->buffer);
  free(writer);
}

void write_entity_values(RowWriter *writer, int fields, ...) {
  va_list args;
  va_start(args, fields);

  switch (writer->mode) {
    case WRITE_MODE_TABLE:
      write_entity_table(writer, fields, args);
      break;
    case WRITE_MODE_CSV:
      write_entity_csv(writer, fields, args);
      break;
    default:
      break;
  }

  va_end(args);
}

void write_entity_csv(RowWriter *writer, int fields, va_list args) {
  char line[BUFFER_SIZE] = "";
  char formatting[BUFFER_SIZE] = "";

  if (writer->row > 0) {
    strcat(formatting, "\n");
  }

  for (int i = 0; i < fields - 1; i++) {
    strcat(formatting, writer->format[i]);
    strcat(formatting, ";");
  }
  strcat(formatting, writer->format[fields - 1]);

  vsnprintf(line, BUFFER_SIZE, formatting, args);

  writer->row++;

  append_to_file_buffer(writer->buffer, line);
}

void write_entity_table(RowWriter *writer, int fields, va_list args) {
  char line[BUFFER_SIZE] = "";
  if (writer->row > 0) {
    strcat(line, "\n\n");
  }

  sprintf(line + strlen(line), "--- %d ---\n", writer->row + 1);
  for (int i = 0; i < fields; i++) {
    if (i > 0) strcat(line, "\n");

    char value[VALUE_BUFFER_SIZE];
    sprintf(value, writer->format[i], va_arg(args, void *));
    strcat(line, writer->field_names[i]);
    strcat(line, ": ");
    strcat(line, value);
  }

  writer->row++;

  append_to_file_buffer(writer->buffer, line);
}