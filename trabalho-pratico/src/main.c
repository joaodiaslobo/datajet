#include <stdio.h>

#include "workers/batch.h"

int main(int argc, char** argv) {
  switch (argc) {
    case 3:
      /* BATCH MODE */
      batch_worker(argv);
      break;
    case 2:
      /* INTERACTIVE MODE */
      printf("Interactive mode hasn't been implemented yet.\n");
      break;
    default:
      break;
  }
}