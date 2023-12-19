/**
 * @file schema_data_types.h
 * @brief Schema data types.
 */
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

/**
 * @brief Parses sex.
 * @param sex Sex string.
 * @return Parsed sex.
 */
Sex parse_sex(char *sex);

/**
 * @brief Transforms sex into string.
 * @param sex Sex.
 * @return Sex string.
 */
char *sex_to_string(Sex sex);

/**
 * @brief Parses payment method.
 * @param payment Payment method string.
 * @return Parsed payment method.
 */
PayMethod parse_payment_method(char *payment);

/**
 * @brief Parses account status.
 * @param status Account status string.
 * @return Parsed account status.
 */
AccountStatus parse_account_status(char *status);

/**
 * @brief Parses timestamp.
 * @param timestamp_string Timestamp string.
 * @return Parsed timestamp.
 */
Timestamp parse_timestamp(char *timestamp_string);

/**
 * @brief Transforms timestamp into string.
 * @param timestamp Timestamp.
 * @return Timestamp string.
 */
char *timestamp_to_string(Timestamp timestamp);

/**
 * @brief Transforms date into string.
 * @param timestamp Timestamp.
 * @return Date string.
 */
char *date_to_string(Timestamp timestamp);

/**
 * @brief Parses date.
 * @param date_string Date string.
 * @return Parsed timestamp date.
 */
Timestamp parse_date(char *date_string);

/**
 * @brief Gets difference between two timestamps in days.
 * @param timestamp1 First timestamp.
 * @param timestamp2 Second timestamp.
 * @return Time difference in days.
 */
int timestamp_get_difference_in_days(Timestamp timestamp1,
                                     Timestamp timestamp2);

/**
 * @brief Gets difference between two timestamps in seconds.
 * @param timestamp1 First timestamp.
 * @param timestamp2 Second timestamp.
 * @return Time difference in seconds.
 */
int difference_in_seconds_between_timestamps(Timestamp timestamp1,
                                             Timestamp timestamp2);

/**
 * @brief Gets difference between two timestamps in years.
 * @param timestamp1 First timestamp.
 * @param timestamp2 Second timestamp.
 * @return Time difference in years.
 */
int difference_in_years_between_dates(int date1, int date2);

/**
 * @brief Checks if a timestamp is between two dates.
 * @param timestamp Timestamp checked.
 * @param begin_date Begin date.
 * @param end_date End date.
 * @return true if it's comprehended by the two dates, false if not.
 */
bool is_timestamp_between_dates(Timestamp timestamp, Timestamp begin_date,
                                Timestamp end_date);

/**
 * @brief Parses number.
 * @param number_string Number string.
 * @return Parsed number.
 */
int parse_number(char *number_string);

/**
 * @brief Parses number to an unsigned integer.
 * @param number_string Number string.
 * @return Parsed unsigned integer.
 */
unsigned int parse_unsigned_integer(char *int_string);

/**
 * @brief Parses boolean.
 * @param boolean_string Boolean string.
 * @return Parsed boolean.
 */
bool parse_boolean(char *boolean_string);

/**
 * @brief Transforms all string's chars into uppercase chars.
 * @param string String.
 */
void string_to_upper(char *string);

#endif