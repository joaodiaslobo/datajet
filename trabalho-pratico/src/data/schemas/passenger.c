#include "data/schemas/passenger.h"

#include <glib.h>
#include <stdint.h>

#include "data/catalogs/catalog_passenger.h"
#include "data/schemas/schema_data_types.h"
#include "data/schemas/validation/generic_validation.h"
#include "data/statistics/user_flight.h"
#include "io/parsing/reader.h"

int parse_passenger_and_add_to_catalog(RowReader* reader, void* catalog,
                                       void* database) {
  char* passenger_flight_id = reader_next_cell(reader);
  if (is_empty_value(passenger_flight_id)) return 1;
  int flight_id_int = parse_number(passenger_flight_id);

  char* passenger_user_id = reader_next_cell(reader);
  if (is_empty_value(passenger_user_id)) return 1;

  if (passenger_invalid_association(database, passenger_user_id, flight_id_int))
    return 1;

  char passenger_user_key[strlen(passenger_user_id) + 1];
  strcpy(passenger_user_key, passenger_user_id);

  insert_passenger(catalog, flight_id_int, passenger_user_key);

  return 0;
}

bool passenger_invalid_association(void* database, char* user_id,
                                   int flight_id) {
  return !validate_passenger_association(database, user_id, flight_id);
}