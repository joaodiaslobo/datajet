#include <sys/resource.h>
#include <time.h>

#include "data/database.h"
#include "io/file.h"
#include "io/formatting.c"
#include "io/interpreter.h"
#include "program.h"
#include "workers/comparer.c"

#define BUFFER_SIZE 1024
#define NUMBER_OF_QUERIES 10

/*
 * Main testing logic.
 */
static void run_tests(char *dataset_directory, char *commands_file_path,
                      char *expected_output_directory) {
  print("> Starting tests:\n", DEFAULT, BOLD);

  double total_execution_time = 0;

  /* Parse data, create and populate testing database */
  clock_t begin = clock();
  Program *program = initialize_program(PROGRAM_MODE_BATCH);
  Database *database_test = program_get_database(program);
  csv_populate_database(database_test, dataset_directory);
  clock_t end = clock();

  double database_elapsed_time = (double)(end - begin) / CLOCKS_PER_SEC;
  total_execution_time += database_elapsed_time;

  print("[INFO] Database initialization and seeding (elapsed time: %fs) ",
        DEFAULT, REGULAR, database_elapsed_time);
  print("[OK]\n", GREEN, REGULAR);

  /* Get memory usage */
  struct rusage r_usage;
  getrusage(RUSAGE_SELF, &r_usage);

  double average_query_times[NUMBER_OF_QUERIES] = {0};
  double times_query_was_executed[NUMBER_OF_QUERIES] = {0};

  /* Parse commands and execute them */
  FILE *commands_file = open_file(commands_file_path);
  int command_id = 0;
  if (commands_file == NULL) {
    print("[ERROR] Could not open commands input file.\n", RED, BOLD);
    return;
  }

  double query_time = 0;

  char command[BUFFER_SIZE] = "";
  while (fgets(command, BUFFER_SIZE, commands_file) != NULL) {
    int query_id;
    char command_args[BUFFER_SIZE] = " ";
    sscanf(command, "%d%[^\n]", &query_id, command_args);
    strcat(command_args, "\n");
    clock_t begin = clock();
    int result = execute_command_and_save_result(query_id - 1, database_test,
                                                 command_args, command_id);
    clock_t end = clock();
    double elapsed_time = (double)(end - begin) / CLOCKS_PER_SEC;
    query_time += elapsed_time;
    if (result != -1) {
      print("[INFO] (Command %3d) Query %2d (elapsed time: %fs) ", DEFAULT,
            REGULAR, command_id + 1, query_id, elapsed_time);

      /* Check if output is correct */
      char *expected_output_file_path = g_strdup_printf(
          "%s/command%d_output.txt", expected_output_directory, command_id + 1);
      char *output_file_path =
          g_strdup_printf("Resultados/command%d_output.txt", command_id + 1);
      int result = file_compare(expected_output_file_path, output_file_path);

      g_free(output_file_path);
      g_free(expected_output_file_path);

      if (result == -1) {
        print("[OK]\n", GREEN, REGULAR);
      } else {
        print("[WR]\n", RED, REGULAR);
        print("[INFO] ", DEFAULT, REGULAR);
        print("(Command %3d) wrong on line %d\n", RED, REGULAR, command_id + 1,
              result + 1);
      }
      times_query_was_executed[query_id - 1]++;
      average_query_times[query_id - 1] =
          average_query_times[query_id - 1] +
          (elapsed_time - average_query_times[query_id - 1]) /
              (times_query_was_executed[query_id - 1]);
      total_execution_time += elapsed_time;
    } else {
      print("[INFO] (Command %3d) Query %2d ", DEFAULT, REGULAR, command_id + 1,
            query_id);
      print("                          [NO]\n", YELLOW, REGULAR);
    }

    command_id++;
  }

  /* Free database's structures and data */
  begin = clock();
  free_database(database_test);
  end = clock();

  double free_elapsed_time = (double)(end - begin) / CLOCKS_PER_SEC;

  print("[INFO] Freeing database structures (elapsed time: %fs) ", DEFAULT,
        REGULAR, free_elapsed_time);
  print("[OK]\n", GREEN, REGULAR);

  for (int i = 0; i < NUMBER_OF_QUERIES; i++) {
    if (times_query_was_executed[i] == 0) {
      continue;
    }
    print("[INFO] Average execution time for Query %2d: %fs\n", DEFAULT,
          REGULAR, i + 1, average_query_times[i]);
  }

  print("[INFO] Database initialization and seeding (elapsed time: %fs) \n",
        DEFAULT, REGULAR, database_elapsed_time);

  print("[INFO] Total queries execution time: %fs\n", DEFAULT, REGULAR,
        query_time);
  print("[INFO] Total execution time: %fs\n", DEFAULT, REGULAR,
        total_execution_time);
  print("[INFO] Max memory usage: %ld KB\n", DEFAULT, REGULAR,
        r_usage.ru_maxrss);
  print("> Tests finished.\n", DEFAULT, BOLD);

  close_file(commands_file);
}