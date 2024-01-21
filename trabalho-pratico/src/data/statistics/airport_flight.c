#include "data/statistics/airport_flight.h"

#include <stdbool.h>

#include "data/catalogs/catalog_airport.h"
#include "data/catalogs/catalog_flight.h"
#include "data/database.h"

void create_airport_flight_association(Database *database, Flight *flight) {
  CatalogAirport *airports_catalog = database_get_airport_catalog(database);
  int delay = difference_in_seconds_between_timestamps(
      flight_get_schedule_departure_date(flight),
      flight_get_real_departure_date(flight));
  char *airport_id = flight_get_origin(flight);
  insert_airport_delay(airports_catalog, airport_id, delay);
  g_free(airport_id);
}
