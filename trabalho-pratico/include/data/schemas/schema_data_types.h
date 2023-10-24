#ifndef schema_data_types_H
#define schema_data_types_H

#include <stdbool.h>

typedef enum sex { F = 0, M = 1 } Sex;

typedef struct timestamp {
  int date;
  int time;
} Timestamp;

typedef enum pay_method { CASH = 0, CREDIT = 1, DEBIT = 2 } PayMethod;

typedef enum account_status { ACTIVE = 0, INACTIVE = 1 } AccountStatus;

Sex parse_sex(char *sex);

PayMethod parse_payment_method(char *payment);

AccountStatus parse_account_status(char *status);

Timestamp *parse_timestamp(char *timestamp_string);

Timestamp *parse_date(char *date_string);

int parse_number(char *number_string);

bool parse_boolean(char *boolean_string);

void string_to_upper(char *string);

#endif