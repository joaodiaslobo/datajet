#ifndef READER_H
#define READER_H

typedef struct rowReader RowReader;

void reader_set_row(RowReader *reader, char *string);

RowReader *initialize_row_reader(char *string, char delimiter);

void *reader_next_cell(RowReader *reader);

char *reader_current_cell(RowReader *reader);

void free_row_reader(RowReader *reader);

#endif