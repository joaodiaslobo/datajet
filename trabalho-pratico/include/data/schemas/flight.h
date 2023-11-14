#ifndef FLIGHT_H
#define FLIGHT_H

#include "data/schemas/schema_data_types.h"
#include "io/parsing/reader.h"

typedef struct flight Flight;

Flight* create_flight(char* id, char* airline, char* plane_model,
                      int total_seats, char* origin, char* destination,
                      Timestamp schedule_departure_date,
                      Timestamp schedule_arrival_date,
                      Timestamp real_departure_date,
                      Timestamp real_arrival_date, char* pilot, char* copilot,
                      char* notes);

void free_flight(void* flight_ptr);

int parse_flight_and_add_to_catalog(RowReader* reader, void* catalog,
                                    void* database);

void validate_flights(void* catalog, void* database);

char* flight_get_id(Flight* flight);

char* flight_get_airline(Flight* flight);

char* flight_get_plane_model(Flight* flight);

int flight_get_total_seats(Flight* flight);

#endif