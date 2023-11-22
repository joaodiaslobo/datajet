#include "data/schemas/validation/generic_validation.h"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

bool is_empty_value(char* value) { return (strlen(value) == 0); }

bool invalid_date(char* date) {
  if (strlen(date) != 10 || date[4] != '/' || date[7] != '/') return true;

  char temp_date[11] = "";
  strcat(temp_date, date);

  for (int i = 0; i < 4; i++) {
    if (!isdigit(temp_date[i])) return true;
  }

  temp_date[7] = '\0';
  int month = parse_number(temp_date + 5);
  int day = parse_number(temp_date + 8);

  return (month <= 0 || month > 12 || day <= 0 || day > 31);
}

bool invalid_timestamp(char* timestamp) {
  if (strlen(timestamp) == 19 && timestamp[10] == ' ' && timestamp[13] == ':' &&
      timestamp[16] == ':') {
    char temp[11];
    strncpy(temp, timestamp, 10);
    temp[10] = '\0';
    if (invalid_date(temp)) return true;
    int aux = 0;

    // validate hours
    if (!isdigit(timestamp[11]) || !isdigit(timestamp[12]))
      return true;
    else
      aux = (timestamp[11] - '0') * 10 + (timestamp[12] - '0');
    if (aux > 23) return true;

    // validate minutes
    if (!isdigit(timestamp[14]) || !isdigit(timestamp[15]))
      return true;
    else
      aux = (timestamp[14] - '0') * 10 + (timestamp[15] - '0');
    if (aux > 60) return true;

    // validate seconds
    if (!isdigit(timestamp[17]) || !isdigit(timestamp[18]))
      return true;
    else
      aux = (timestamp[17] - '0') * 10 + (timestamp[18] - '0');
    if (aux > 60) return true;
    return false;
  }
  return true;
}

bool compare_date(char* start_date, char* end_date) {
  return ((parse_date(start_date).date) < (parse_date(end_date).date));
}

bool compare_timestamp(char* start_timestamp, char* end_timestamp) {
  return (((parse_timestamp(start_timestamp).date) <
           (parse_timestamp(end_timestamp).date)) ||
          (((parse_timestamp(start_timestamp).date) ==
            (parse_timestamp(end_timestamp).date)) &&
           ((parse_timestamp(start_timestamp).time) <
            (parse_timestamp(end_timestamp).time))));
}

bool invalid_value_length(int length, char* value) {
  return !((int)strlen(value) == length);
}

bool invalid_bool_value(char* value) {
  for (int i = 0; i < (int)strlen(value); i++) {
    value[i] = tolower(value[i]);
  }
  return !(strcmp(value, "0") == 0 || strcmp(value, "f") == 0 ||
           strcmp(value, "false") == 0 || strcmp(value, "1") == 0 ||
           strcmp(value, "t") == 0 || strcmp(value, "true") == 0 ||
           strcmp(value, "") == 0);
}

bool invalid_positive_integer(char* value) {
  int value_length = strlen(value);

  if (value_length == 0) return true;
  if (value[0] == 48) return true;

  for (int i = 0; i < value_length; i++) {
    if (value[i] < 48 || value[i] > 57) return true;
  }
  return false;
}

bool invalid_integer(char* value) {
  int value_length = strlen(value);

  if (value_length == 0) return true;
  for (int i = 0; i < value_length; i++) {
    if (value[i] < 48 || value[i] > 57) return true;
  }
  return false;
}