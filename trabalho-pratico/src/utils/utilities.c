#include "utils/utilities.h"

#include <stdbool.h>

void trim_leading_whitespace(char *string) {
  int index = 0;
  for (; string[index] == ' ' || string[index] == '\t' || string[index] == '\n';
       index++)
    ;

  if (index != 0) {
    int i;
    for (i = 0; string[i + index] != '\0'; i++) {
      string[i] = string[i + index];
    }
    string[i] = '\0';
  }
}

bool starts_with(char *string, char *prefix) {
  if (strncmp(string, prefix, strlen(prefix)) == 0) return 1;
  return 0;
}