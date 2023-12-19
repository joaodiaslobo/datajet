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
Flight* create_flight(unsigned int id, char* airline, char* plane_model,
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
unsigned int flight_get_id(Flight* flight);

/**
 * @brief Sets flight's id.
 * @param flight Flight.
 * @param id Id.
 */
void flight_set_id(Flight* flight, unsigned int id);

/**
 * @brief Gets flight's airline.
 * @param flight Flight.
 * @return Flight's airline.
 */
char* flight_get_airline(Flight* flight);

/**
 * @brief Sets flight's airline.
 * @param flight Flight.
 * @param airline Airline.
 */
void flight_set_airline(Flight* flight, char* airline);

/**
 * @brief Gets flight's plane model.
 * @param flight Flight.
 * @return Flight's plane model.
 */
char* flight_get_plane_model(Flight* flight);

/**
 * @brief Sets flight's plane model.
 * @param flight Flight.
 * @param plane_model Plane model.
 */
void flight_set_plane_model(Flight* flight, char* plane_model);

/**
 * @brief Gets flight's total seats.
 * @param flight Flight.
 * @return Flight's total seats.
 */
int flight_get_total_seats(Flight* flight);

/**
 * @brief Sets flight's total seats.
 * @param flight Flight.
 * @param total_seats Total seats.
 */
void flight_set_total_seats(Flight* flight, int total_seats);

/**
 * @brief Gets flight's origin airport.
 * @param flight Flight.
 * @return Flight's origin airport.
 */
char* flight_get_origin(Flight* flight);

/**
 * @brief Sets flight's origin.
 * @param flight Flight.
 * @param origin Origin.
 */
void flight_set_origin(Flight* flight, char* origin);

/**
 * @brief Gets flight's destination airport.
 * @param flight Flight.
 * @return Flight's destination airport.
 */
char* flight_get_destination(Flight* flight);

/**
 * @brief Sets flight's destination.
 * @param flight Flight.
 * @param destination Destination.
 */
void flight_set_destination(Flight* flight, char* destination);

/**
 * @brief Gets flight's schedule departure date.
 * @param flight Flight.
 * @return Flight's schedule departure date.
 */
Timestamp flight_get_schedule_departure_date(Flight* flight);

/**
 * @brief Sets flight's schedule departure date.
 * @param flight Flight.
 * @param schedule_departure_date Schedule departure date.
 */
void flight_set_schedule_departure_date(Flight* flight,
                                        Timestamp schedule_departure_date);

/**
 * @brief Gets flight's schedule arrival date.
 * @param flight Flight.
 * @return Flight's schedule arrival date.
 */
Timestamp flight_get_schedule_arrival_date(Flight* flight);

/**
 * @brief Sets flight's schedule arrival date.
 * @param flight Flight.
 * @param schedule_arrival_date Schedule arrival date.
 */
void flight_set_schedule_arrival_date(Flight* flight,
                                      Timestamp schedule_arrival_date);

/**
 * @brief Gets flight's real departure date.
 * @param flight Flight.
 * @return Flight's real departure date.
 */
Timestamp flight_get_real_departure_date(Flight* flight);

/**
 * @brief Sets flight's real departure date.
 * @param flight Flight.
 * @param real_departure_date Real departure date.
 */
void flight_set_real_departure_date(Flight* flight,
                                    Timestamp real_departure_date);

/**
 * @brief Gets flight's real arrival date.
 * @param flight Flight.
 * @return Flight's real arrival date.
 */
Timestamp flight_get_real_arrival_date(Flight* flight);

/**
 * @brief Sets flight's real arrival date.
 * @param flight Flight.
 * @param real_arrival_date Real arrival date.
 */
void flight_set_real_arrival_date(Flight* flight, Timestamp real_arrival_date);
/**
 * @brief Gets flight's pilot.
 * @param flight Flight.
 * @return Flight's pilot.
 */
char* flight_get_pilot(Flight* flight);

/**
 * @brief Sets flight's pilot.
 * @param flight Flight.
 * @param pilot Pilot.
 */
void flight_set_pilot(Flight* flight, char* pilot);

/**
 * @brief Gets flight's copilot.
 * @param flight Flight.
 * @return Flight's copilot.
 */
char* flight_get_copilot(Flight* flight);

/**
 * @brief Sets flight's copilot.
 * @param flight Flight.
 * @param copilot Copilot.
 */
void flight_set_copilot(Flight* flight, char* copilot);

/**
 * @brief Gets flight's notes.
 * @param flight Flight.
 * @return Flight's notes.
 */
char* flight_get_notes(Flight* flight);

/**
 * @brief Sets flight's notes.
 * @param flight Flight.
 * @param notes Notes.
 */
void flight_set_notes(Flight* flight, char* notes);

#endif