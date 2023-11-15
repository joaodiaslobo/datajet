#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

#include "data/database.h"
#include "io/parsing/reader.h"

typedef int(EntityLineParser)(RowReader *, void *, void *);

typedef void(WriteEntityValidationOutput)(FILE *, char *);

void read_csv(FILE *input_file, FILE *output_file,
              EntityLineParser *entity_line_parser,
              WriteEntityValidationOutput *write_entity_validation_output,
              void *catalog, void *database);

#endif