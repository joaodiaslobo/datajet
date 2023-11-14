#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

#include "data/database.h"
#include "io/parsing/reader.h"

typedef int(EntityLineParser)(RowReader *, void *, void *);

typedef int(OnEntityParserValidationFailed)(RowReader *, Database *);

void read_csv(FILE *file, EntityLineParser *entity_line_parser, void *catalog,
              void *database);

#endif