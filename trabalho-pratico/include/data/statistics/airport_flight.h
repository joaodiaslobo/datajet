/*
 * @file airport_flight.h
 * @brief Airport associations.
 */
#ifndef STATISTICS_AIRPORT_FLIGHTS_H
#define STATISTICS_AIRPORT_FLIGHTS_H

#include <stdbool.h>

#include "data/database.h"

/**
 * @brief Creates an airport-flight association.
 * @details Creates an association between an airport and a flight.
 *
 * @param database Main database.
 * @param flight Flight.
 */
void create_airport_flight_association(Database *database, Flight *flight);

#endif