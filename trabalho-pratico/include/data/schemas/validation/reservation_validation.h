/**
 * @file reservation_validation.h
 * @brief Reservation data validation.
 */
#ifndef RESERVATION_VALIDATION_H
#define RESERVATION_VALIDATION_H

#include "data/schemas/schema_data_types.h"

/**
 * @brief Check if the given string represents a valid hotel stars value.
 * @details Allows only integers between 1 and 5.
 *
 * @param value The input string to be checked.
 * @return true if the string is an invalid hotel stars value, false otherwise.
 */
bool invalid_hotel_stars(char* hotel_stars);

/**
 * @brief Check if the given string represents a valid city tax value.
 * @details Allows only zero or positive integers.
 *
 * @param value The input string to be checked.
 * @return true if the string is an invalid city tax value, false otherwise.
 */
bool invalid_city_tax(char* city_tax);

/**
 * @brief Check if the given string represents a valid rating value.
 * @details Allows only integers between 1 and 5 or empty values.
 *
 * @param value The input string to be checked.
 * @return true if the string is an invalid rating value, false otherwise.
 */
bool invalid_rating(char* rating);

#endif