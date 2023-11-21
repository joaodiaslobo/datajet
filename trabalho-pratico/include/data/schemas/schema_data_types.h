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

char *sex_to_string(Sex sex);

PayMethod parse_payment_method(char *payment);

AccountStatus parse_account_status(char *status);

Timestamp parse_timestamp(char *timestamp_string);

char *timestamp_to_string(Timestamp timestamp);

char *date_to_string(Timestamp timestamp);

Timestamp parse_date(char *date_string);

int timestamp_get_difference_in_days(Timestamp timestamp1,
                                     Timestamp timestamp2);

int difference_in_seconds_between_timestamps(Timestamp timestamp1,
                                             Timestamp timestamp2);

int difference_in_years_between_dates(int date1, int date2);

bool is_timestamp_between_dates(Timestamp timestamp, Timestamp begin_date,
                                Timestamp end_date);

int parse_number(char *number_string);

bool parse_boolean(char *boolean_string);

void string_to_upper(char *string);

#endif