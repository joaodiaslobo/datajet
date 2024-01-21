/*
 * @file airport_passenger.h
 * @brief Airport associations.
 */
#ifndef STATISTICS_AIRPORT_PASSENGERS_H
#define STATISTICS_AIRPORT_PASSENGERS_H

#include <stdbool.h>

#include "data/database.h"

/**
 * @brief Creates an airport-passenger association.
 * @details Creates an association between an airport and a passenger.
 *
 * @param database Main database.
 * @param flight_id Flight id.
 */
void create_passenger_year_airport_association(Database *database,
                                               unsigned int flight_id);

#endif