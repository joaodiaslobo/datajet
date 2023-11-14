/**
 * @file user_validation.c
 * @brief Validation of the user data
 */

/*
 *   Copyright 2023 Hélder Gomes, João Lobo, Rita Camacho
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

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
