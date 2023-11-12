#ifndef WRITER_H
#define WRITER_H

#include <stdarg.h>

typedef enum write_mode { WRITE_MODE_CSV = 0, WRITE_MODE_TABLE = 1 } WriteMode;

typedef struct rowWriter RowWriter;

RowWriter *initialize_row_writer(char *file_name, WriteMode writeMode);

void free_row_writer(RowWriter *writer);

void row_writer_set_field_names(RowWriter *writer, char **field_names);

void row_writer_set_formatting(RowWriter *writer, char **formatting);

void free_and_finish_writing_row(RowWriter *writer);

void write_entity_values(RowWriter *writer, int fields, ...);

void write_entity_csv(RowWriter *writer, int fields, va_list args);

void write_entity_table(RowWriter *writer, int fields, va_list args);

#endif