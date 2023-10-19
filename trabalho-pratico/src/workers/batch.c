#include "workers/batch.h"

#include <stdio.h>

int batch_worker(char **argv) {
  printf("== BATCH MODE ==\n");
  char *dataset_folder_path = argv[0];
  char *output_folder_path = argv[1];
  printf("DATASETS PATH: %s\n", dataset_folder_path);
  printf("OUTPUT PATH: %s\n", output_folder_path);
  return 0;
}