#ifndef PASSENGER_H
#define PASSENGER_H

#include <stdbool.h>

#include "io/parsing/reader.h"

typedef struct passenger Passenger;

int parse_passenger_and_add_to_catalog(RowReader* reader, void* catalog,
                                       void* database);

bool passenger_invalid_association(void* database, char* user_id,
                                   int flight_id);

#endif