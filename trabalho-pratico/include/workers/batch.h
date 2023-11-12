#ifndef BATCH_H
#define BATCH_H

#include "data/database.h"

int batch_worker(char **argv, Database *database);

void parse_and_execute_commands(char *query_commands_path, Database *database);

void execute_command_and_save_result(int query_id, Database *database,
                                     char *command_args, int command_id);

#endif