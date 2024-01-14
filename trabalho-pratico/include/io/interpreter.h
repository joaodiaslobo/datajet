/**
 * @file interpreter.h
 * @brief Responsible for parsing and executing commands.
 */
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "data/database.h"

/**
 * @brief Output directory for the command results.
 */
#define OUTPUT_DIRECTORY "Resultados"

/**
 * @brief Output file naming structure for the command result.
 */
#define OUTPUT_FILE_NAME "command%d_output.txt"

/**
 * @brief Parses and executes commands.
 * @details Parses and executes commands from a file.
 *
 * @param query_commands_path Path to the file containing the commands.
 * @param database Main database.
 */
void parse_and_execute_commands(char *query_commands_path, Database *database);

/**
 * @brief Executes a command and saves the result.
 * @details Executes a command and saves the result to a file.
 *
 * @param query_id Query id.
 * @param database Main database.
 * @param command_args Command arguments.
 * @param command_id Command id.
 * @return 0 if successful, -1 otherwise.
 */
int execute_command_and_save_result(int query_id, Database *database,
                                    char *command_args, int command_id);

#endif