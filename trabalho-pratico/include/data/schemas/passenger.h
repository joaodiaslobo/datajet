#ifndef PASSENGER_H
#define PASSENGER_H

#include "io/parsing/reader.h"

typedef struct passenger Passenger;

Passenger* create_passenger(char* flight_id, char* user_id);

void free_passenger(void* passenger_ptr);

int parse_passenger_and_add_to_catalog(RowReader* reader, void* catalog);

char* passenger_get_user_id(Passenger* passenger);

char* passenger_get_flight_id(Passenger* passenger);

#endif