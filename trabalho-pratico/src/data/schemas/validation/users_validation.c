#include "data/schemas/validation/users_validation.h"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int invalid_email(char* email) {
  int i = 0, len = 0;
  // cycle for the username
  for (i = 0; email[i] != '@' && email[i] != '\0'; i++) {
    len++;
  }
  if (len < 1 || email[i] == '\0') return 1;
  len = 0;
  // cycle for the domain
  for (i++; email[i] != '.' && email[i] != '\0'; i++) {
    len++;
  }
  if (len < 1 || email[i] == '\0') return 1;
  len = 0;
  // cycle for the TLD
  for (i++; email[i] != '\0'; i++) {
    len++;
  }
  if (len < 2) return 1;
  return 0;
}