#include "data/schemas/passenger.h"

#include <glib.h>
#include <stdint.h>

#include "data/catalogs/catalog_passenger.h"
#include "data/schemas/schema_data_types.h"
#include "io/parsing/reader.h"

struct passenger {
  char* flight_id;
  char* user_id;
};

Passenger* create_passenger(char* flight_id, char* user_id) {
  Passenger* passenger = malloc(sizeof(struct passenger));

  passenger->flight_id = g_strdup(flight_id);
  passenger->user_id = g_strdup(user_id);

  return passenger;
}

void free_passenger(void* passenger_ptr) {
  Passenger* passenger = (Passenger*)passenger_ptr;
  g_free(passenger->flight_id);
  g_free(passenger->user_id);
  free(passenger);
}

int parse_passenger_and_add_to_catalog(RowReader* reader, void* catalog) {
  char* passenger_flight_id = reader_next_cell(reader);
  char* passenger_user_id = reader_next_cell(reader);
  Passenger* passenger =
      create_passenger(passenger_flight_id, passenger_user_id);

  insert_passenger(catalog, passenger);

  return 0;
}

char* passenger_get_user_id(Passenger* passenger) { return passenger->user_id; }

char* passenger_get_flight_id(Passenger* passenger) {
  return passenger->flight_id;
}