#include "data/schemas/schema_data_types.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

Sex parse_sex(char *sex) { return strcmp(sex, "F") || 1; }

PayMethod parse_payment_method(char *payment) {
  if (strcmp(payment, "cash"))
    return CASH;
  else if (strcmp(payment, "credit_card"))
    return CREDIT;
  return DEBIT;
}

AccountStatus parse_account_status(char *status) {
  string_to_upper(status);
  return strcmp(status, "ACTIVE");
}

Timestamp parse_timestamp(char *timestamp_string) {
  int date = 0;
  int time = 0;

  date += (timestamp_string[0] - '0') * 10000000;
  date += (timestamp_string[1] - '0') * 1000000;
  date += (timestamp_string[2] - '0') * 100000;
  date += (timestamp_string[3] - '0') * 10000;

  date += (timestamp_string[5] - '0') * 1000;
  date += (timestamp_string[6] - '0') * 100;

  date = (timestamp_string[8] - '0') * 10;
  date += (timestamp_string[9] - '0');

  time += (timestamp_string[11] - '0') * 100000;
  time += (timestamp_string[12] - '0') * 10000;

  time += (timestamp_string[14] - '0') * 1000;
  time += (timestamp_string[15] - '0') * 100;

  time += (timestamp_string[17] - '0') * 10;
  time += (timestamp_string[18] - '0');

  return (Timestamp){.date = date, .time = time};
}

Timestamp parse_date(char *date_string) {
  int date = 0;

  date += (date_string[0] - '0') * 10000000;
  date += (date_string[1] - '0') * 1000000;
  date += (date_string[2] - '0') * 100000;
  date += (date_string[3] - '0') * 10000;

  date += (date_string[5] - '0') * 1000;
  date += (date_string[6] - '0') * 100;

  date = (date_string[8] - '0') * 10;
  date += (date_string[9] - '0');

  return (Timestamp){.date = date, .time = 0};
}

int parse_number(char *number_string) {
  int number = 0;
  for (int i = 0; number_string[i] != '\0'; i++) {
    number *= 10;
    number += number_string[i] - '0';
  }
  return number;
}

bool parse_boolean(char *boolean_string) {
  string_to_upper(boolean_string);
  return boolean_string[0] == 'T' || boolean_string[0] == '1';
}

void string_to_upper(char *string) {
  for (int i = 0; string[i] != '\0'; i++) {
    string[i] = toupper(string[i]);
  }
}