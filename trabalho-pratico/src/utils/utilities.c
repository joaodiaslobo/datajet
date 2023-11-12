#include "utils/utilities.h"

void trim_leading_whitespace(char* string) {
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