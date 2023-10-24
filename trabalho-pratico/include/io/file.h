#ifndef FILE_H
#define FILE_H

#include <stdio.h>

FILE *open_file(char *path);

void close_file(FILE *file);

char *build_full_file_path(char *folder, char *file_name);

#endif