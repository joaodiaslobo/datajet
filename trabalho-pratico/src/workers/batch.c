#include "workers/batch.h"

#include <stdio.h>

#include "data/database.h"
#include "io/interpreter.h"

int batch_worker(char **argv, Database *database) {
  printf("== BATCH MODE ==\n");
  char *dataset_folder_path = argv[0];
  char *query_commands_path = argv[1];

  csv_populate_database(database, dataset_folder_path);

  parse_and_execute_commands(query_commands_path, database);

  return 0;
}