/**
 * @file file.h
 * @brief Responsible for handling file operations.
 */
#ifndef FILE_H
#define FILE_H

#include <stdio.h>

/**
 * @brief Structure that holds a file buffer.
 */
typedef struct fileBuffer FileBuffer;

/**
 * @brief Opens a file.
 *
 * @param path Path to the file.
 * @return Opened file.
 */
FILE *open_file(char *path);

/**
 * @brief Creates a file to append data.
 *
 * @param path Path to the file.
 * @return Created file.
 */
FILE *create_file_to_append(char *path);

/**
 * @brief Writes data to a file.
 *
 * @param file File to write to.
 * @param data Data to be written.
 */
void write_data_to_file(FILE *file, char *data);

/**
 * @brief Closes a file.
 *
 * @param file File to be closed.
 */
void close_file(FILE *file);

/**
 * @brief Builds a full file path.
 *
 * @param folder Folder where the file is located.
 * @param file_name Name of the file.
 * @return Full file path.
 */
char *build_full_file_path(char *folder, char *file_name);

/**
 * @brief Initializes a file buffer.
 *
 * @param name Name of the file.
 * @return File buffer.
 */
FileBuffer *initialize_file_buffer(char *name);

/**
 * @brief Frees a file buffer.
 *
 * @param buffer File buffer to be freed.
 */
void free_file_buffer(FileBuffer *buffer);

/**
 * @brief Appends content to a file buffer.
 *
 * @param buffer File buffer to append to.
 * @param content Content to be appended.
 */
void append_to_file_buffer(FileBuffer *buffer, char *content);

/**
 * @brief Writes the file buffer data from memory to disk as an actual file.
 *
 * @param buffer File buffer to be written.
 */
void write_file_buffer(FileBuffer *buffer);

/**
 * @brief Creates a directory if it doesn't exist.
 *
 * @param path Path to the directory.
 */
void create_directory_if_doesnt_exist(char *path);

#endif