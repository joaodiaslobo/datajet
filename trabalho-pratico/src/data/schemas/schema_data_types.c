#include "data/schemas/schema_data_types.h"

#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Sex parse_sex(char *sex) {
  int female_cmp = strcmp(sex, "F");
  if (female_cmp == 0) {
    return F;
  }
  return M;
}

char *sex_to_string(Sex sex) {
  char *sex_string;
  switch (sex) {
    case F:
      sex_string = g_strdup("F");
      break;
    default:
      sex_string = g_strdup("M");
      break;
  }

  return sex_string;
}

PayMethod parse_payment_method(char *payment) {
  if (strcmp(payment, "cash"))
    return CASH;
  else if (strcmp(payment, "credit_card"))
    return CREDIT;
  return DEBIT;
}

AccountStatus parse_account_status(char *status) {
  string_to_upper(status);
  return strcmp(status, "INACTIVE") == 0;
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

  date += (timestamp_string[8] - '0') * 10;
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

  date += (date_string[8] - '0') * 10;
  date += (date_string[9] - '0');

  return (Timestamp){.date = date, .time = 0};
}

char *timestamp_to_string(Timestamp timestamp) {
  int date = timestamp.date;
  int time = timestamp.time;

  unsigned short year = date / 10000;
  unsigned short month = (date / 100) % 100;
  unsigned short day = date % 100;

  unsigned short hour = time / 10000;
  unsigned short minute = (time / 100) % 100;
  unsigned short second = time % 100;

  char *timestamp_string = (char *)malloc(20 * sizeof(char));

  sprintf(timestamp_string, "%04hu/%02hu/%02hu %02hu:%02hu:%02hu", year, month,
          day, hour, minute, second);

  return timestamp_string;
}

char *date_to_string(Timestamp timestamp) {
  int date = timestamp.date;

  int year = date / 10000;
  int month = (date / 100) % 100;
  int day = date % 100;

  char *date_string = (char *)malloc(20 * sizeof(char));

  sprintf(date_string, "%04d/%02d/%02d", year, month, day);

  return date_string;
}

int timestamp_get_difference_in_days(Timestamp timestamp1,
                                     Timestamp timestamp2) {
  int day1 = timestamp1.date % 100;
  int day2 = timestamp2.date % 100;

  return day2 - day1;
}

int difference_in_seconds_between_timestamps(Timestamp timestamp1,
                                             Timestamp timestamp2) {
  // Extract year, month, and day from date
  int year1 = timestamp1.date / 10000;
  int month1 = (timestamp1.date / 100) % 100;
  int day1 = timestamp1.date % 100;

  int year2 = timestamp2.date / 10000;
  int month2 = (timestamp2.date / 100) % 100;
  int day2 = timestamp2.date % 100;

  // Extract hour, minute, and second from time
  int hour1 = timestamp1.time / 10000;
  int minute1 = (timestamp1.time / 100) % 100;
  int second1 = timestamp1.time % 100;

  int hour2 = timestamp2.time / 10000;
  int minute2 = (timestamp2.time / 100) % 100;
  int second2 = timestamp2.time % 100;

  // Calculate total minutes
  int total_seconds_1 = (day1 * 24 * 60 + hour1 * 60 + minute1) * 60;
  int total_seconds_2 = (day2 * 24 * 60 + hour2 * 60 + minute2) * 60;

  // Calculate the difference in minutes
  int difference = total_seconds_2 - total_seconds_1;

  return difference;
}

int difference_in_years_between_dates(int date1, int date2) {
  int year1 = date1 / 10000;
  int month1 = (date1 / 100) % 100;
  int day1 = date1 % 100;

  int year2 = date2 / 10000;
  int month2 = (date2 / 100) % 100;
  int day2 = date2 % 100;

  int yearDiff = year2 - year1;

  if (month2 < month1 || (month2 == month1 && day2 < day1)) {
    yearDiff--;
  }

  return yearDiff;
}

bool is_timestamp_between_dates(Timestamp timestamp, Timestamp begin_date,
                                Timestamp end_date) {
  return (
      (timestamp.date > begin_date.date && timestamp.date < end_date.date) ||
      (timestamp.date == begin_date.date && timestamp.date < end_date.date &&
       timestamp.time >= begin_date.time) ||
      (timestamp.date > begin_date.date && timestamp.date == end_date.date &&
       timestamp.time <= end_date.time) ||
      (timestamp.date == begin_date.date && timestamp.date == end_date.date &&
       timestamp.time >= begin_date.time && timestamp.time <= end_date.time));
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