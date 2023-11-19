/**
 * @file utilities.h
 * @brief General utilities.
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdbool.h>

/**
 * @brief Trims the leading whitespace of a string.
 *
 * @param string String to be trimmed.
 */
void trim_leading_whitespace(char *string);

/**
 * @brief Checks if a string starts with a prefix.
 *
 * @param string String to be checked.
 */
bool starts_with(char *string, char *prefix);

/**
 * @brief Checks if a string ends with a suffix.
 *
 * @param string String to be checked.
 */
bool ends_with(char *string, char *suffix);

#endif