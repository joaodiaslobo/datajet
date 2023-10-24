#include "io/parsing/reader.h"

#include <glib.h>

struct rowReader {
  char *row;
  char delimiter;
};

void reader_set_row(RowReader *reader, char *string) { reader->row = string; }

RowReader *initialize_row_reader(char *string, char delimiter) {
  RowReader *reader = malloc(sizeof(struct rowReader));

  reader->row = string;
  reader->delimiter = delimiter;

  return reader;
}

void *reader_next_cell(RowReader *reader) {
  char *start = reader->row;

  while (*reader->row != reader->delimiter && *reader->row != '\0') {
    reader->row++;
  }

  if (*reader->row == reader->delimiter) {
    *reader->row = '\0';
    reader->row++;
  }

  return start;
}

char *reader_current_cell(RowReader *reader) { return g_strdup(reader->row); }

void free_row_reader(RowReader *reader) { free(reader); }
