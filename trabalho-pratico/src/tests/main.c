#include "test.c"

int main(int argc, char *argv[]) {
  if (argc != 4) {
    print("Wrong number of arguments given.\n", RED, BOLD);
    print(
        "Usage: %s <dataset_directory> <commands_file_path> "
        "<expected_output_directory>\n",
        DEFAULT, REGULAR, argv[0]);
    return -1;
  }

  char *dataset_directory = argv[1];
  char *commands_file_path = argv[2];
  char *expected_output_directory = argv[3];

  run_tests(dataset_directory, commands_file_path, expected_output_directory);

  return 0;
}
