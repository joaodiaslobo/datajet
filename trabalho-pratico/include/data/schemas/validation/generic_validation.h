/**
 * @file generic_validation.h
 * @brief Generic data validation
 */

#ifndef GENERIC_VALIDATION_H
#define GENERIC_VALIDATION_H

#include "data/schemas/schema_data_types.h"

/**
 * @brief Verify if the receiving value is empty
 * @details Checks if the given string is empty or null.
 *
 * @param value The input string to be checked.
 * @return true if the string is empty or null, false otherwise.
 */
bool is_empty_value(char* value);

/**
 * @brief Check if the given date string is invalid.
 * @details Validates the date format (yyyy/mm/dd) and values.
 *
 * @param date The input date string to be checked.
 * @return true if the date is invalid, false otherwise.
 */
bool invalid_date(char* date);

/**
 * @brief Check if the given timestamp string is invalid.
 * @details Validates the timestamp format (yyyy/mm/dd hh:mm:ss) and values.
 *
 * @param timestamp The input timestamp string to be checked.
 * @return true if the timestamp is invalid, false otherwise.
 */
bool invalid_timestamp(char* timestamp);

/**
 * @brief Compare two date strings.
 * @details Parses the date strings and compares them.
 *
 * @param start_date The start date string.
 * @param end_date The end date string.
 * @return true if the start date is earlier than the end date, false otherwise.
 */
bool compare_date(char* start_date, char* end_date);

/**
 * @brief Compare two timestamp strings.
 * @details Parses the timestamp strings and compares them.
 *
 * @param start_timestamp The start timestamp string.
 * @param end_timestamp The end timestamp string.
 * @return true if the start timestamp is earlier than the end timestamp, false
 * otherwise.
 */
bool compare_timestamp(char* start_timestamp, char* end_timestamp);

/**
 * @brief Check if the length of the given value is invalid.
 * @details Compares the length of the value with the specified length.
 *
 * @param length The expected length.
 * @param value The input value string to be checked.
 * @return true if the length is invalid, false otherwise.
 */
bool invalid_value_length(int length, char* value);

/**
 * @brief Check if the given string represents a valid boolean value.
 * @details Case-insensitive comparison for boolean values.
 *
 * @param value The input string to be checked.
 * @return true if the string is a valid boolean value, false otherwise.
 */
bool invalid_bool_value(char* value);

/**
 * @brief Check if the given string represents a valid positive integer.
 * @details Allows only non-zero positive integers.
 *
 * @param value The input string to be checked.
 * @return true if the string is an invalid positive integer, false otherwise.
 */
bool invalid_positive_integer(char* value);

bool invalid_integer(char* value);

#endif