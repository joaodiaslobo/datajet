#include "data/schemas/validation/user_validation.h"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

bool invalid_email(char* email) {
  int i = 0, len = 0;
  // cycle for the username
  for (i = 0; email[i] != '@' && email[i] != '\0'; i++) {
    len++;
  }
  if (len < 1 || email[i] == '\0') return true;
  len = 0;
  // cycle for the domain
  for (i++; email[i] != '.' && email[i] != '\0'; i++) {
    len++;
  }
  if (len < 1 || email[i] == '\0') return true;
  len = 0;
  // cycle for the TLD
  for (i++; email[i] != '\0'; i++) {
    len++;
  }
  if (len < 2) return true;
  return false;
}

bool invalid_account_status(char* account_status) {
  for (int i = 0; i < (int)strlen(account_status); i++) {
    account_status[i] = tolower(account_status[i]);
  }
  return !(strcmp(account_status, "active") == 0 ||
           strcmp(account_status, "inactive") == 0);
}
