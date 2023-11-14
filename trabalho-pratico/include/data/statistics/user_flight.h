#ifndef STATISTICS_PASSENGER_H
#define STATISTICS_PASSENGER_H

#include <stdbool.h>

#include "data/database.h"

bool validate_passenger_association(Database *database, char *user_id,
                                    int flight_id);

bool validate_flight_passenger_count(gpointer key, Flight *flight,
                                     void *database);

void remove_flight_passengers(Database *database, int flight_id);

void remove_user_passengers(Database *database, char *user_id);

int get_count_of_flights_belonging_to_user(Database *database, char *user_id);

int get_count_of_users_belonging_to_flight(Database *database, int flight_id);

#endif