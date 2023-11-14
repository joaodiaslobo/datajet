#include "io/parsing/parser.h"

#include <stdio.h>
#include <string.h>

#include "io/parsing/reader.h"

#define BUFFER_SIZE 1024
#define DELIMITER ';'

void read_csv(FILE *file, EntityLineParser *entity_line_parser, void *catalog,
              void *database) {
  char buffer[BUFFER_SIZE];

  if (fgets(buffer, BUFFER_SIZE, file) == NULL) return;

  RowReader *reader = initialize_row_reader(buffer, DELIMITER);

  while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
    int line_length = strlen(buffer);
    if (buffer[line_length - 1] == '\n') {
      buffer[line_length - 1] = '\0';
    }

    reader_set_row(reader, buffer);

    entity_line_parser(reader, catalog, database);
  }

  free_row_reader(reader);
}