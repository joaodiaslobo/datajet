#include "data/schemas/flight.h"

#include <glib.h>

#include "data/catalogs/catalog_flight.h"
#include "data/schemas/schema_data_types.h"
#include "io/parsing/reader.h"

struct flight {
  char* id;
  char* airline;
  char* plane_model;
  int total_seats;
  char* origin;
  char* destination;
  Timestamp* schedule_departure_date;
  Timestamp* schedule_arrival_date;
  Timestamp* real_departure_date;
  Timestamp* real_arrival_date;
  char* pilot;
  char* copilot;
  char* notes;
};

Flight* create_flight(char* id, char* airline, char* plane_model,
                      int total_seats, char* origin, char* destination,
                      Timestamp* schedule_departure_date,
                      Timestamp* schedule_arrival_date,
                      Timestamp* real_departure_date,
                      Timestamp* real_arrival_date, char* pilot, char* copilot,
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
  free(flight->schedule_departure_date);
  free(flight->schedule_arrival_date);
  free(flight->real_departure_date);
  free(flight->real_arrival_date);
  g_free(flight->pilot);
  g_free(flight->copilot);
  g_free(flight->notes);
  free(flight);
}

int parse_flight_and_add_to_catalog(RowReader* reader, void* catalog) {
  char* flight_id = reader_next_cell(reader);
  char* flight_airline = reader_next_cell(reader);
  char* flight_plane_model = reader_next_cell(reader);
  int flight_total_seats = parse_number(reader_next_cell(reader));
  char* flight_origin = reader_next_cell(reader);
  char* flight_destination = reader_next_cell(reader);
  Timestamp* flight_schedule_departure_date =
      parse_timestamp(reader_next_cell(reader));
  Timestamp* flight_schedule_arrival_date =
      parse_timestamp(reader_next_cell(reader));
  Timestamp* flight_real_departure_date =
      parse_timestamp(reader_next_cell(reader));
  Timestamp* flight_real_arrival_date =
      parse_timestamp(reader_next_cell(reader));
  char* flight_pilot = reader_next_cell(reader);
  char* flight_copilot = reader_next_cell(reader);
  char* flight_notes = reader_next_cell(reader);

  Flight* flight = create_flight(
      flight_id, flight_airline, flight_plane_model, flight_total_seats,
      flight_origin, flight_destination, flight_schedule_departure_date,
      flight_schedule_arrival_date, flight_real_departure_date,
      flight_real_arrival_date, flight_pilot, flight_copilot, flight_notes);

  insert_flight(catalog, flight);

  return 0;
}

char* flight_get_id(Flight* flight) { return g_strdup(flight->id); }

char* flight_get_airline(Flight* flight) { return g_strdup(flight->airline); }

char* flight_get_plane_model(Flight* flight) {
  return g_strdup(flight->plane_model);
}

int flight_get_total_seats(Flight* flight) { return flight->total_seats; }