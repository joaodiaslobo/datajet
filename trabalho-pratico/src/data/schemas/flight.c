#include "data/schemas/flight.h"

#include <glib.h>
#include <stdint.h>

#include "data/schemas/schemas_utilities.h"

struct flight {
  char* id;
  char* airline;
  char* plane_model;
  uint16_t total_seats;  // Platform independent
  char* origin;
  char* destination;
  Date schedule_departure_date;
  Date schedule_arrival_date;
  Date real_departure_date;
  Date real_arrival_date;
  char* pilot;
  char* copilot;
  char* notes;
};

Flight* create_flight(char* id, char* airline, char* plane_model,
                      uint16_t total_seats, char* origin, char* destination,
                      Date schedule_departure_date, Date schedule_arrival_date,
                      Date real_departure_date, Date real_arrival_date,
                      char* pilot, char* copilot, char* notes) {
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

void free_flight(Flight* flight) {
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