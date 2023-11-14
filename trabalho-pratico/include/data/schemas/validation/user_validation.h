/**
 * @file user_validation.h
 * @brief Validation of the user data
 */

/*
 *   Copyright 2023 Hélder Gomes, João Lobo, Rita Camacho
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
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
