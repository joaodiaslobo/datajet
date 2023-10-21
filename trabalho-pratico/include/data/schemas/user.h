#ifndef USER_H
#define USER_H

#include <stdint.h>

#include "data/schemas/schemas_utilities.h"

typedef struct user User;

User* create_user(char* id, char* name, char* email, char* phone_number,
                  Date birth_date, Sex sex, char* passport, char* country_code,
                  char* address, Date account_creation, PayMethod pay_method,
                  AccountStatus account_status);

void free_user(User* user);

#endif