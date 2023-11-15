#include "io/parsing/parser.h"

#include <stdio.h>
#include <string.h>

#include "io/parsing/reader.h"

#define BUFFER_SIZE 1024
#define DELIMITER ';'

void read_csv(FILE *input_file, FILE *output_file,
              EntityLineParser *entity_line_parser,
              WriteEntityValidationOutput *write_entity_validation_output,
              void *catalog, void *database) {
  char buffer[BUFFER_SIZE];

  if (fgets(buffer, BUFFER_SIZE, input_file) == NULL) return;

  write_entity_validation_output(output_file, buffer);

  RowReader *reader = initialize_row_reader(buffer, DELIMITER);

  while (fgets(buffer, BUFFER_SIZE, input_file) != NULL) {
    int line_length = strlen(buffer);
    char *original_line = g_strdup(buffer);
    if (buffer[line_length - 1] == '\n') {
      buffer[line_length - 1] = '\0';
    }

    reader_set_row(reader, buffer);

    int result = entity_line_parser(reader, catalog, database);

    if (result == 1) {
      write_entity_validation_output(output_file, original_line);
    }

    g_free(original_line);
  }

  free_row_reader(reader);
}