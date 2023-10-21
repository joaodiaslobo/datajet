#include "data/schemas/passenger.h"

#include <glib.h>
#include <stdint.h>

#include "data/schemas/schemas_utilities.h"

struct passenger {
  char* user_id;
  char* flight_id;
};

Passenger* create_passenger(char* user_id, char* flight_id) {
  Passenger* passenger = malloc(sizeof(struct passenger));

  passenger->user_id = g_strdup(user_id);
  passenger->flight_id = g_strdup(flight_id);

  return passenger;
}

void free_passenger(Passenger* passenger) {
  g_free(passenger->user_id);
  g_free(passenger->flight_id);
  free(passenger);
}