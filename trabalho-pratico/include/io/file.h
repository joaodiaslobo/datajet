#ifndef FILE_H
#define FILE_H

#include <stdio.h>

typedef struct fileBuffer FileBuffer;

FILE *open_file(char *path);

void close_file(FILE *file);

char *build_full_file_path(char *folder, char *file_name);

FileBuffer *initialize_file_buffer(char *name);

void free_file_buffer(FileBuffer *buffer);

void append_to_file_buffer(FileBuffer *buffer, char *content);

void write_file_buffer(FileBuffer *buffer);

void create_directory_if_doesnt_exist(char *path);

#endif