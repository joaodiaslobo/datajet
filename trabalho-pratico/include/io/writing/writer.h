/**
 * @file writer.h
 * @brief Responsible for writing the results of the commands to files with
 * multiple formatting options.
 */
#ifndef WRITER_H
#define WRITER_H

#include <stdarg.h>

/**
 * @brief Write mode.
 * @details Write mode that the writer is running on.
 */
typedef enum write_mode {
  WRITE_MODE_CSV = 0,
  WRITE_MODE_TABLE = 1,
  WRITE_MODE_INTERACTIVE = 2
} WriteMode;

/**
 * @brief Row writer.
 * @details Responsible for writing the results of the commands to files with
 * multiple formatting options.
 */
typedef struct rowWriter RowWriter;

/**
 * @brief Initializes a row writer.
 * @details Initializes a row writer with the given file name and write mode.
 *
 * @param file_name Name of the file to write to.
 * @param writeMode Write mode.
 * @return Initialized row writer.
 */
RowWriter *initialize_row_writer(char *file_name, WriteMode writeMode);

/**
 * @brief Gets the number of rows of the row writer.
 * @details Gets the number of rows of the row writer.
 *
 * @param writer Row writer.
 * @return Number of rows.
 */
int row_writer_get_number_of_rows(RowWriter *writer);

/**
 * @brief Gets the field names of the row writer.
 * @details Gets the field names of the row writer.
 *
 * @param writer Row writer.
 * @return Field names.
 */
char *row_writer_get_field_name(RowWriter *writer, int index);

/**
 * @brief Frees a row writer.
 * @details Frees the data used by the row writer.
 *
 * @param writer Row writer.
 */
void free_row_writer(RowWriter *writer);

/**
 * @brief Sets the field names of the row writer.
 * @details Sets the field names of the row writer.
 *
 * @param writer Row writer.
 * @param field_names Field names.
 */
void row_writer_set_field_names(RowWriter *writer, char **field_names,
                                int fields);

/**
 * @brief Sets the formatting of the row writer.
 * @details Sets the formatting of the row writer.
 *
 * @param writer Row writer.
 * @param formatting Formatting.
 */
void row_writer_set_formatting(RowWriter *writer, char **formatting);

/**
 * @brief Gets the number of fields of the row writer.
 * @details Gets the number of fields of the row writer.
 *
 * @param writer Row writer.
 * @return Number of fields.
 */
int row_writer_get_number_of_fields(RowWriter *writer);

/**
 * @brief Writes the buffer to the file.
 * @details Writes the buffer to the file.
 *
 * @param writer Row writer.
 */
void row_writer_write_buffer(RowWriter *writer);

/**
 * @brief Writes a row to the file.
 * @details Writes a row to the file.
 *
 * @param writer Row writer.
 * @param fields Number of fields to be written.
 * @param args Arguments to be written.
 */
void free_and_finish_writing_row(RowWriter *writer);

/**
 * @brief Writes a new row.
 * @details Writes a new entity row to the writer.
 *
 * @param writer Row writer.
 * @param fields Number of fields to be written.
 * @param args Arguments to be written.
 */
void write_entity_values(RowWriter *writer, int fields, ...);

/**
 * @brief Writes a new row.
 * @details Writes a new csv formatted entity row to the writer.
 *
 * @param writer Row writer.
 * @param fields Number of fields to be written.
 * @param args Arguments to be written.
 */
void write_entity_csv(RowWriter *writer, int fields, va_list args);

/**
 * @brief Writes a new row.
 * @details Writes a new table formatted entity row to the writer.
 *
 * @param writer Row writer.
 * @param fields Number of fields to be written.
 * @param args Arguments to be written.
 */
void write_entity_table(RowWriter *writer, int fields, va_list args);

/**
 * @brief Writes a new row.
 * @details Writes a new formatted entity row to the writer.
 *
 * @param writer Row writer.
 * @param fields Number of fields to be written.
 * @param args Arguments to be written.
 */
void write_entity_interactive(RowWriter *writer, int fields, va_list args);

#endif