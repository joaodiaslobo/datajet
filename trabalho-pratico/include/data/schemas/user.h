#ifndef USER_H
#define USER_H

#include <stdint.h>

#include "data/schemas/schema_data_types.h"
#include "io/parsing/reader.h"

typedef struct user User;

User* create_user(char* id, char* name, char* email, char* phone_number,
                  Timestamp birth_date, Sex sex, char* passport,
                  char* country_code, char* address, Timestamp account_creation,
                  PayMethod pay_method, AccountStatus account_status);

void free_user(void* user_ptr);

int parse_user_and_add_to_catalog(RowReader* reader, void* catalog,
                                  void* database);

char* user_get_id(User* user);

char* user_get_name(User* user);

char* user_get_email(User* user);

char* user_get_phone_number(User* user);

Timestamp user_get_birth_date(User* user);

Sex user_get_sex(User* user);

char* user_get_passport(User* user);

char* user_get_country_code(User* user);

char* user_get_address(User* user);

Timestamp user_get_account_creation(User* user);

PayMethod user_get_pay_method(User* user);

AccountStatus user_get_account_status(User* user);

#endif