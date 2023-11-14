#include "data/schemas/flight.h"

#include <glib.h>

#include "data/catalogs/catalog_flight.h"
#include "data/schemas/schema_data_types.h"
#include "data/schemas/validation/generic_validation.h"
#include "data/statistics/user_flight.h"
#include "io/parsing/reader.h"

struct flight {
  char* id;
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

Flight* create_flight(char* id, char* airline, char* plane_model,
                      int total_seats, char* origin, char* destination,
                      Timestamp schedule_departure_date,
                      Timestamp schedule_arrival_date,
                      Timestamp real_departure_date,
                      Timestamp real_arrival_date, char* pilot, char* copilot,
                      char* notes) {
  Flight* flight = malloc(sizeof(struct flight));

  flight->id = g_strdup(id);
  flight->airline = g_strdup(airline);
  flight->plane_model = g_strdup(plane_model);
  flight->total_seats = total_seats;
  flight->origin = g_strdup(origin);
  flight->destination = g_strdup(destination);
  flight->schedule_departure_date = schedule_departure_date;
  flight->schedule_arrival_date = schedule_arrival_date;
  flight->real_departure_date = real_departure_date;
  flight->real_arrival_date = real_arrival_date;
  flight->pilot = g_strdup(pilot);
  flight->copilot = g_strdup(copilot);
  flight->notes = g_strdup(notes);

  return flight;
}

void free_flight(void* flight_ptr) {
  Flight* flight = (Flight*)flight_ptr;
  g_free(flight->id);
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
  char* flight_id = reader_next_cell(reader);
  if (is_empty_value(flight_id)) return 1;
  int flight_id_int = parse_number(flight_id);
  gpointer flight_key = GINT_TO_POINTER(flight_id_int);

  char* flight_airline = reader_next_cell(reader);
  if (is_empty_value(flight_airline)) return 1;

  char* flight_plane_model = reader_next_cell(reader);
  if (is_empty_value(flight_plane_model)) return 1;

  char* flight_total_seats_string = reader_next_cell(reader);
  if (invalid_positive_integer(flight_total_seats_string)) return 1;
  int flight_total_seats = parse_number(flight_total_seats_string);

  char* flight_origin = reader_next_cell(reader);
  if (invalid_value_length(3, flight_origin)) return 1;

  char* flight_destination = reader_next_cell(reader);
  if (invalid_value_length(3, flight_destination)) return 1;

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
  foreach_flight_remove(catalog, validate_flight_passenger_count, database);
}

char* flight_get_id(Flight* flight) { return g_strdup(flight->id); }

char* flight_get_airline(Flight* flight) { return g_strdup(flight->airline); }

char* flight_get_plane_model(Flight* flight) {
  return g_strdup(flight->plane_model);
}

int flight_get_total_seats(Flight* flight) { return flight->total_seats; }

char* flight_get_origin(Flight* flight) { return g_strdup(flight->origin); }

char* flight_get_destination(Flight* flight) {
  return g_strdup(flight->destination);
}

Timestamp flight_get_schedule_departure_date(Flight* flight) {
  return flight->schedule_departure_date;
}

Timestamp flight_get_schedule_arrival_date(Flight* flight) {
  return flight->schedule_arrival_date;
}

Timestamp flight_get_real_departure_date(Flight* flight) {
  return flight->real_departure_date;
}

Timestamp flight_get_real_arrival_date(Flight* flight) {
  return flight->real_arrival_date;
}

char* flight_get_pilot(Flight* flight) { return g_strdup(flight->pilot); }

char* flight_get_copilot(Flight* flight) { return g_strdup(flight->copilot); }

char* flight_get_notes(Flight* flight) { return g_strdup(flight->notes); }