/**
 * @file reader.h
 * @brief Used by the parser to traverse a csv formatted line.
 */

#ifndef READER_H
#define READER_H

/**
 * @brief Structure that helps traverse a csv formatted line.
 */
typedef struct rowReader RowReader;

/**
 * @brief Sets the current row of the reader.
 *
 * @param reader Reader to be set.
 * @param string String to be set as the current row.
 */
void reader_set_row(RowReader *reader, char *string);

/**
 * @brief Initializes a row reader.
 *
 * @param string First row to be read.
 * @param delimiter Delimiter used in the file.
 * @return Row reader.
 */
RowReader *initialize_row_reader(char *string, char delimiter);

/**
 * @brief Make the reader point to the next cell in the row being read.
 *
 * @param reader Row reader.
 */
void *reader_next_cell(RowReader *reader);

/**
 * @brief Returns the current cell of the row being read.
 *
 * @param reader Row reader.
 * @return Current cell.
 */
char *reader_current_cell(RowReader *reader);

/**
 * @brief Frees the row reader.
 *
 * @param reader Row reader to be freed.
 */
void free_row_reader(RowReader *reader);

#endif