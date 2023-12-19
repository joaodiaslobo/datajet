/*
 * @file user_flight.h
 * @brief Passenger associations.
 */
#ifndef STATISTICS_PASSENGER_H
#define STATISTICS_PASSENGER_H

#include <stdbool.h>

#include "data/database.h"

/**
 * @brief Creates a passenger association.
 * @details Creates a passenger association between a user and a flight.
 *
 * @param database Main database.
 * @param user_id User id.
 * @param flight_id Flight id.
 */
void create_passenger_association(Database *database, char *user_id,
                                  unsigned int flight_id);

/**
 * @brief Validates a passenger association.
 * @details Validates a passenger association between a user and a flight.
 *
 * @param database Main database.
 * @param user_id User id.
 * @param flight_id Flight id.
 * @return true if the association is valid.
 */
bool validate_passenger_association(Database *database, char *user_id,
                                    unsigned int flight_id);

/**
 * @brief Validates the passenger count of a flight.
 * @details Validates the passenger count of a flight.
 *
 * @param key Flight id.
 * @param flight Flight.
 * @param database Main database.
 * @return true if the passenger count is valid.
 */
bool validate_flight_passenger_count(gpointer key, Flight *flight,
                                     void *database);

/**
 * @brief Removes all passengers from a flight.
 * @details Removes all passengers associated with a flight.
 *
 * @param database Main database.
 * @param flight_id Flight id.
 */
void remove_flight_passengers(Database *database, unsigned int flight_id);

/**
 * @brief Removes all passengers from a user.
 * @details Removes all passengers associated with a user.
 *
 * @param database Main database.
 * @param user_id User id.
 */
void remove_user_passengers(Database *database, char *user_id);

/**
 * @brief Gets the count of flights belonging to a user.
 * @details Removes all passengers associated with a user.
 *
 * @param database Main database.
 * @param user_id User id.
 * @return Count of flights belonging to a user.
 */
int get_count_of_flights_belonging_to_user(Database *database, char *user_id);

/**
 * @brief Gets the count of users belonging to a flight.
 * @details Gets the count of users associated with a flight.
 *
 * @param database Main database.
 * @param flight_id Flight id.
 * @return Count of users belonging to a flight.
 */
int get_count_of_users_belonging_to_flight(Database *database,
                                           unsigned int flight_id);

#endif