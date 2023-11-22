/**
 * @file parser.h
 * @brief Generic parser for csv formatted entity data.
 */
#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

#include "data/database.h"
#include "io/parsing/reader.h"

/**
 * @brief Maximum size for a line in the csv file.
 */
#define BUFFER_SIZE 1024

/**
 * @brief Delimiter used in the csv file.
 */
#define DELIMITER ';'

/**
 * @brief Function that takes the parsed data and uses it to form an abstract
 * entity.
 */
typedef int(EntityLineParser)(RowReader *, void *, void *);

/**
 * @brief Function that gets called when entity_line_parser fails to build the
 * entity.
 */
typedef void(WriteEntityValidationOutput)(FILE *, char *);

/**
 * @brief Generic parser
 * @details Generic parser for csv formatted entity data that reads a file and
 * calls a abstract entity builder.
 *
 * @param input_file File to be parsed.
 * @param output_file File to output lines that failed building.
 * @param entity_line_parser Function that takes the parsed data and uses it to
 * form an abstract entity.
 * @param write_entity_validation_output Function that gets called when
 * entity_line_parser fails to build the entity.
 */
void read_csv(FILE *input_file, FILE *output_file,
              EntityLineParser *entity_line_parser,
              WriteEntityValidationOutput *write_entity_validation_output,
              void *catalog, void *database);

#endif