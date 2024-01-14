#include "io/interpreter.h"

#include <stdio.h>

#include "data/database.h"
#include "data/queries.h"
#include "io/file.h"
#include "io/writing/writer.h"
#include "utils/utilities.h"

#define BUFFER_SIZE 1024

void parse_and_execute_commands(char *query_commands_path, Database *database) {
  FILE *commands_file = open_file(query_commands_path);
  int command_id = 0;
  if (commands_file == NULL) return;

  char command[BUFFER_SIZE] = "";
  while (fgets(command, BUFFER_SIZE, commands_file) != NULL) {
    int query_id;
    char command_args[BUFFER_SIZE] = " ";
    sscanf(command, "%d%[^\n]", &query_id, command_args);
    strcat(command_args, "\n");
    execute_command_and_save_result(query_id - 1, database, command_args,
                                    command_id);
    command_id++;
  }

  close_file(commands_file);
}

int execute_command_and_save_result(int query_id, Database *database,
                                    char *command_args, int command_id) {
  WriteMode writeMode;
  char flag;
  char query_args[BUFFER_SIZE] = " ";

  sscanf(command_args, "%c%[^\n]", &flag, query_args);

  trim_leading_whitespace(query_args);

  switch (flag) {
    case 'F':
      writeMode = WRITE_MODE_TABLE;
      break;
    default:
      writeMode = WRITE_MODE_CSV;
      break;
  }

  create_directory_if_doesnt_exist(OUTPUT_DIRECTORY);

  char *output_file =
      g_strdup_printf(OUTPUT_DIRECTORY "/" OUTPUT_FILE_NAME, command_id + 1);
  RowWriter *writer = initialize_row_writer(output_file, writeMode);

  int result =
      execute_query_and_save_result(writer, database, query_id, query_args);

  if (result != -1) {
    free_and_finish_writing_row(writer);
  } else {
    // printf("[WARN] Query %d not implemented.\n", query_id + 1);
    free_row_writer(writer);
  }
  g_free(output_file);

  return result;
}