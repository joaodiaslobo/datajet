#include "data/schemas/flight.h"

#include <glib.h>

#include "data/catalogs/catalog_flight.h"
#include "data/schemas/schema_data_types.h"
#include "data/schemas/validation/generic_validation.h"
#include "data/statistics/user_flight.h"
#include "io/parsing/reader.h"

struct flight {
  unsigned int id;
  char* airline;
  char* plane_model;
  int total_seats;
  char* origin;
  char* destination;
  Timestamp schedule_departure_date;
  Timestamp schedule_arrival_date;
  Timestamp real_departure_date;
  Timestamp real_arrival_date;
  char* pilot;
  char* copilot;
  char* notes;
};

Flight* create_flight(unsigned int id, char* airline, char* plane_model,
                      int total_seats, char* origin, char* destination,
                      Timestamp schedule_departure_date,
                      Timestamp schedule_arrival_date,
                      Timestamp real_departure_date,
                      Timestamp real_arrival_date, char* pilot, char* copilot,
                      char* notes) {
  Flight* flight = malloc(sizeof(struct flight));

  flight_set_id(flight, id);
  flight_set_airline(flight, airline);
  flight_set_plane_model(flight, plane_model);
  flight_set_total_seats(flight, total_seats);
  flight_set_origin(flight, origin);
  flight_set_destination(flight, destination);
  flight_set_schedule_departure_date(flight, schedule_departure_date);
  flight_set_schedule_arrival_date(flight, schedule_arrival_date);
  flight_set_real_departure_date(flight, real_departure_date);
  flight_set_real_arrival_date(flight, real_arrival_date);
  flight_set_pilot(flight, pilot);
  flight_set_copilot(flight, copilot);
  flight_set_notes(flight, notes);

  return flight;
}

void free_flight(void* flight_ptr) {
  Flight* flight = (Flight*)flight_ptr;
  g_free(flight->airline);
  g_free(flight->plane_model);
  g_free(flight->origin);
  g_free(flight->destination);
  g_free(flight->pilot);
  g_free(flight->copilot);
  g_free(flight->notes);
  free(flight);
}

int parse_flight_and_add_to_catalog(RowReader* reader, void* catalog,
                                    void* database) {
  char* flight_id_string = reader_next_cell(reader);
  if (is_empty_value(flight_id_string)) return 1;
  unsigned int flight_id = parse_unsigned_integer(flight_id_string);
  gpointer flight_key = GUINT_TO_POINTER(flight_id);

  char* flight_airline = reader_next_cell(reader);
  if (is_empty_value(flight_airline)) return 1;

  char* flight_plane_model = reader_next_cell(reader);
  if (is_empty_value(flight_plane_model)) return 1;

  char* flight_total_seats_string = reader_next_cell(reader);
  if (invalid_positive_integer(flight_total_seats_string)) return 1;
  int flight_total_seats = parse_number(flight_total_seats_string);

  char* flight_origin = reader_next_cell(reader);
  if (invalid_value_length(3, flight_origin)) return 1;
  string_to_upper(flight_origin);

  char* flight_destination = reader_next_cell(reader);
  if (invalid_value_length(3, flight_destination)) return 1;
  string_to_upper(flight_destination);

  char* flight_schedule_departure_date_string = reader_next_cell(reader);
  if (invalid_timestamp(flight_schedule_departure_date_string)) return 1;
  Timestamp flight_schedule_departure_date =
      parse_timestamp(flight_schedule_departure_date_string);

  char* flight_schedule_arrival_date_string = reader_next_cell(reader);
  if (invalid_timestamp(flight_schedule_arrival_date_string)) return 1;
  Timestamp flight_schedule_arrival_date =
      parse_timestamp(flight_schedule_arrival_date_string);

  if ((flight_schedule_departure_date.date >
       flight_schedule_arrival_date.date) ||
      (flight_schedule_departure_date.date ==
           flight_schedule_arrival_date.date &&
       flight_schedule_departure_date.time >=
           flight_schedule_arrival_date.time))
    return 1;

  char* flight_real_departure_date_string = reader_next_cell(reader);
  if (invalid_timestamp(flight_real_departure_date_string)) return 1;
  Timestamp flight_real_departure_date =
      parse_timestamp(flight_real_departure_date_string);

  char* flight_real_arrival_date_string = reader_next_cell(reader);
  if (invalid_timestamp(flight_real_arrival_date_string)) return 1;
  Timestamp flight_real_arrival_date =
      parse_timestamp(flight_real_arrival_date_string);

  if ((flight_real_departure_date.date > flight_real_arrival_date.date) ||
      (flight_real_departure_date.date == flight_real_arrival_date.date &&
       flight_real_departure_date.time >= flight_real_arrival_date.time))
    return 1;

  char* flight_pilot = reader_next_cell(reader);
  if (is_empty_value(flight_pilot)) return 1;

  char* flight_copilot = reader_next_cell(reader);
  if (is_empty_value(flight_copilot)) return 1;

  char* flight_notes = reader_next_cell(reader);

  Flight* flight = create_flight(
      flight_id, flight_airline, flight_plane_model, flight_total_seats,
      flight_origin, flight_destination, flight_schedule_departure_date,
      flight_schedule_arrival_date, flight_real_departure_date,
      flight_real_arrival_date, flight_pilot, flight_copilot, flight_notes);

  insert_flight(catalog, flight, flight_key);
  return 0;
}

void validate_flights(void* catalog, void* database) {
  foreach_flight_remove(catalog, (GHRFunc)validate_flight_passenger_count,
                        database);
}

unsigned int flight_get_id(Flight* flight) { return flight->id; }

void flight_set_id(Flight* flight, unsigned int id) { flight->id = id; }

char* flight_get_airline(Flight* flight) { return g_strdup(flight->airline); }

void flight_set_airline(Flight* flight, char* airline) {
  flight->airline = g_strdup(airline);
}

char* flight_get_plane_model(Flight* flight) {
  return g_strdup(flight->plane_model);
}

void flight_set_plane_model(Flight* flight, char* plane_model) {
  flight->plane_model = g_strdup(plane_model);
}

int flight_get_total_seats(Flight* flight) { return flight->total_seats; }

void flight_set_total_seats(Flight* flight, int total_seats) {
  flight->total_seats = total_seats;
}

char* flight_get_origin(Flight* flight) { return g_strdup(flight->origin); }

void flight_set_origin(Flight* flight, char* origin) {
  flight->origin = g_strdup(origin);
}

char* flight_get_destination(Flight* flight) {
  return g_strdup(flight->destination);
}

void flight_set_destination(Flight* flight, char* destination) {
  flight->destination = g_strdup(destination);
}

Timestamp flight_get_schedule_departure_date(Flight* flight) {
  return flight->schedule_departure_date;
}

void flight_set_schedule_departure_date(Flight* flight,
                                        Timestamp schedule_departure_date) {
  flight->schedule_departure_date = schedule_departure_date;
}

Timestamp flight_get_schedule_arrival_date(Flight* flight) {
  return flight->schedule_arrival_date;
}

void flight_set_schedule_arrival_date(Flight* flight,
                                      Timestamp schedule_arrival_date) {
  flight->schedule_arrival_date = schedule_arrival_date;
}

Timestamp flight_get_real_departure_date(Flight* flight) {
  return flight->real_departure_date;
}

void flight_set_real_departure_date(Flight* flight,
                                    Timestamp real_departure_date) {
  flight->real_departure_date = real_departure_date;
}

Timestamp flight_get_real_arrival_date(Flight* flight) {
  return flight->real_arrival_date;
}

void flight_set_real_arrival_date(Flight* flight, Timestamp real_arrival_date) {
  flight->real_arrival_date = real_arrival_date;
}

char* flight_get_pilot(Flight* flight) { return g_strdup(flight->pilot); }

void flight_set_pilot(Flight* flight, char* pilot) {
  flight->pilot = g_strdup(pilot);
}

char* flight_get_copilot(Flight* flight) { return g_strdup(flight->copilot); }

void flight_set_copilot(Flight* flight, char* copilot) {
  flight->copilot = g_strdup(copilot);
}

char* flight_get_notes(Flight* flight) { return g_strdup(flight->notes); }

void flight_set_notes(Flight* flight, char* notes) {
  flight->notes = g_strdup(notes);
}