#include "data/schemas/validation/generic_validation.h"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int empty_error(char* error) {
  if (error == NULL) {
    return 0;
  } else {
    return 1;
  }
}

int invalid_date(char* date) {
  char* temp = date;
  if (strlen(temp) == 10 && temp[4] == '/' && temp[7] == '/') {
    char* token;
    token = strtok_r(temp, "/", &temp);
    for (int cycle = 0; token != NULL; cycle++) {
      if (cycle == 0 && (!isdigit(token[0]) || !isdigit(token[1]) ||
                         !isdigit(token[2]) || !isdigit(token[3]))) {
        return 1;
      } else if (cycle == 1 && (!isdigit(token[0]) || !isdigit(token[1]) ||
                                parse_number(token) > 12)) {
        return 1;
      } else if (cycle == 2 && (!isdigit(token[0]) || !isdigit(token[1]) ||
                                parse_number(token) > 31)) {
        return 1;
      }
      token = strtok_r(temp, "/", &temp);
    }
    return 0;
  }
  return 1;
}

int invalid_timestamp(char* timestamp) {
  if (strlen(timestamp) == 19 && timestamp[10] == ' ' && timestamp[13] == ':' &&
      timestamp[16] == ':') {
    char temp[11];
    strncpy(temp, timestamp, 10);
    temp[10] = '\0';
    if (invalid_date(temp)) return 1;
    int aux = 0;

    // validate hours
    if (!isdigit(timestamp[11]) || !isdigit(timestamp[12]))
      return 1;
    else
      aux = (timestamp[11] - '0') * 10 + (timestamp[12] - '0');
    if (aux > 23) return 1;

    // validate minutes
    if (!isdigit(timestamp[14]) || !isdigit(timestamp[15]))
      return 1;
    else
      aux = (timestamp[14] - '0') * 10 + (timestamp[15] - '0');
    if (aux > 60) return 1;

    // validate seconds
    if (!isdigit(timestamp[17]) || !isdigit(timestamp[18]))
      return 1;
    else
      aux = (timestamp[17] - '0') * 10 + (timestamp[18] - '0');
    if (aux > 60) return 1;
    return 0;
  }
  return 1;
}

int compare_date(char* start_date, char* end_date) {
  return (parse_date(start_date) < (parse_date(end_date)));
}

int compare_timestamp(char* start_timestamp, char* end_timestamp) {
  return (parse_timestamp(start_timestamp) < (parse_timestamp(end_timestamp)));
}