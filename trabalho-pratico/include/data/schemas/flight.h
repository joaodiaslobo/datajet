#ifndef FLIGHT_H
#define FLIGHT_H

#include <stdint.h>

#include "data/schemas/schemas_utilities.h"

typedef struct flight Flight;

Flight* create_flight(char* id, char* airline, char* plane_model,
                      uint16_t total_seats, char* origin, char* destination,
                      Date schedule_departure_date, Date schedule_arrival_date,
                      Date real_departure_date, Date real_arrival_date,
                      char* pilot, char* copilot, char* notes);

void free_flight(Flight* flight);

#endif