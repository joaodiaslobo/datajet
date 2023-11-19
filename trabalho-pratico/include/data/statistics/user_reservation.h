/*
 * @file user_reservation.h
 * @brief User reservation associations.
 */

#ifndef STATISTICS_USER_RESERVATION_H
#define STATISTICS_USER_RESERVATION_H

#include <stdbool.h>

#include "data/database.h"

/**
 * @brief Validates a reservation association.
 * @details Validates a reservation association.
 *
 * @param database Main database.
 * @return true if the association is valid.
 */
bool validate_reservation_user_association(Database *database, char *user_id);

/**
 * @brief Gets the count of reservations belonging to a user.
 * @details Gets the count of reservations belonging to a user.
 *
 * @param database Main database.
 * @param user_id User id.
 */
int get_count_of_reservations_belonging_to_user(Database *database,
                                                char *user_id);

/**
 * @brief Gets the total spent by a user.
 * @details Gets the total spent by a user, by summing expenses by reservation.
 *
 * @param database Main database.
 * @param user_id User id.
 */
double get_user_total_spent(Database *database, char *user_id);

#endif