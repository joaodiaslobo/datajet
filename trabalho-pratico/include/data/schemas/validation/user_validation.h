/**
 * @file user_validation.h
 * @brief Validation of the user data
 */

#ifndef USER_VALIDATION_H
#define USER_VALIDATION_H

#include "data/schemas/schema_data_types.h"

/**
 * @brief Check if the given string represents a valid email address.
 * @param email The input string to be checked.
 * @return true if the string is an invalid email address, false otherwise.
 */
bool invalid_email(char* email);

/**
 * @brief Check if the given string represents a valid account status.
 * @details Case-insensitive comparison for account status.
 *
 * @param account_status The input string to be checked.
 * @return true if the string is an invalid account status, false otherwise.
 */
bool invalid_account_status(char* account_status);

#endif
