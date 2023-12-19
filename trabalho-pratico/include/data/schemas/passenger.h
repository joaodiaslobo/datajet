/**
 * @file passenger.h
 * @brief Passenger schema.
 */
#ifndef PASSENGER_H
#define PASSENGER_H

#include <stdbool.h>

#include "io/parsing/reader.h"

typedef struct passenger Passenger;

/**
 * @brief Parses passenger and add to catalog.
 * @param reader Reader to be used to read the datasets.
 * @param catalog
 * @param database Main database.
 * @return 0 if the execution succeeded, 1 if it failed.

 */
int parse_passenger_and_add_to_catalog(RowReader* reader, void* catalog,
                                       void* database);

/**
 * @brief Indicates if a passenger association is invalid or not.
 * @param database Main database.
 * @param user_id User id.
 * @param flight_id Flight id.
 * @return true if invalid, false if valid.
 */
bool passenger_invalid_association(void* database, char* user_id,
                                   unsigned int flight_id);

#endif