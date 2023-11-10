#include "workers/batch.h"

#include <stdio.h>

#include "data/database.h"

int batch_worker(char **argv, Database *database) {
  printf("== BATCH MODE ==\n");
  char *dataset_folder_path = argv[0];
  // char *output_folder_path = argv[1];

  csv_populate_database(database, dataset_folder_path);

  return 0;
}