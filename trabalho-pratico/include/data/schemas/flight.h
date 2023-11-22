/**
 * @file flight.h
 * @brief Flight schema.
 */
#ifndef FLIGHT_H
#define FLIGHT_H

#include "data/schemas/schema_data_types.h"
#include "io/parsing/reader.h"

typedef struct flight Flight;

/**
 * @brief Creates flight.
 * @details Initializes flight parameters, creating a new flight.
 *
 * @param id Flight id.
 * @param airline Airline.
 * @param plane_model Plane model.
 * @param total_seats Total seats.
 * @param origin Origin airport.
 * @param destination Destination airport.
 * @param schedule_departure_date Schedule departure date.
 * @param schedule_arrival_date Schedule arrival date.
 * @param real_departure_date Real departure date.
 * @param real_arrival_date Real arrival date.
 * @param pilot Pilot.
 * @param copilot Copilot.
 * @param notes Notes.
 * @return New flight.
 */
Flight* create_flight(unsigned short id, char* airline, char* plane_model,
                      int total_seats, char* origin, char* destination,
                      Timestamp schedule_departure_date,
                      Timestamp schedule_arrival_date,
                      Timestamp real_departure_date,
                      Timestamp real_arrival_date, char* pilot, char* copilot,
                      char* notes);

/**
 * @brief Frees flight.
 * @param flight_ptr Flight pointer.
 */
void free_flight(void* flight_ptr);

/**
 * @brief Parses flight and add to catalog.
 * @param reader Reader to be used to read the datasets.
 * @param catalog
 * @param database Main database.
 * @return 0 if the execution succeeded, 1 if it failed.
 */
int parse_flight_and_add_to_catalog(RowReader* reader, void* catalog,
                                    void* database);

/**
 * @brief Validates flights.
 * @param database Main database.
 */
void validate_flights(void* catalog, void* database);

/**
 * @brief Gets flight's id.
 * @param flight Flight.
 * @return Flight's id.
 */
unsigned short flight_get_id(Flight* flight);

/**
 * @brief Gets flight's airline.
 * @param flight Flight.
 * @return Flight's airline.
 */
char* flight_get_airline(Flight* flight);

/**
 * @brief Gets flight's plane model.
 * @param flight Flight.
 * @return Flight's plane model.
 */
char* flight_get_plane_model(Flight* flight);

/**
 * @brief Gets flight's total seats.
 * @param flight Flight.
 * @return Flight's total seats.
 */
int flight_get_total_seats(Flight* flight);

/**
 * @brief Gets flight's origin airport.
 * @param flight Flight.
 * @return Flight's origin airport.
 */
char* flight_get_origin(Flight* flight);

/**
 * @brief Gets flight's destination airport.
 * @param flight Flight.
 * @return Flight's destination airport.
 */
char* flight_get_destination(Flight* flight);

/**
 * @brief Gets flight's schedule departure date.
 * @param flight Flight.
 * @return Flight's schedule departure date.
 */
Timestamp flight_get_schedule_departure_date(Flight* flight);

/**
 * @brief Gets flight's schedule arrival date.
 * @param flight Flight.
 * @return Flight's schedule arrival date.
 */
Timestamp flight_get_schedule_arrival_date(Flight* flight);

/**
 * @brief Gets flight's real departure date.
 * @param flight Flight.
 * @return Flight's real departure date.
 */
Timestamp flight_get_real_departure_date(Flight* flight);

/**
 * @brief Gets flight's real arrival date.
 * @param flight Flight.
 * @return Flight's real arrival date.
 */
Timestamp flight_get_real_arrival_date(Flight* flight);

/**
 * @brief Gets flight's pilot.
 * @param flight Flight.
 * @return Flight's pilot.
 */
char* flight_get_pilot(Flight* flight);

/**
 * @brief Gets flight's copilot.
 * @param flight Flight.
 * @return Flight's copilot.
 */
char* flight_get_copilot(Flight* flight);

/**
 * @brief Gets flight's notes.
 * @param flight Flight.
 * @return Flight's notes.
 */
char* flight_get_notes(Flight* flight);

#endif