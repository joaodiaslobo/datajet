#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "data/database.h"

#define OUTPUT_DIRECTORY "Resultados"
#define OUTPUT_FILE_NAME "command%d_output.txt"

void parse_and_execute_commands(char *query_commands_path, Database *database);

void execute_command_and_save_result(int query_id, Database *database,
                                     char *command_args, int command_id);

#endif