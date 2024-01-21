#include "data/statistics/airport_passenger.h"

#include <stdbool.h>

#include "data/catalogs/catalog_flight.h"
#include "data/schemas/schema_data_types.h"

void create_passenger_year_airport_association(Database *database,
                                               unsigned int flight_id) {
  CatalogAirport *airports_catalog = database_get_airport_catalog(database);
  Flight *flight = catalog_get_flight_by_id(
      database_get_flight_catalog(database), flight_id);
  char *origin_airport_id = flight_get_origin(flight);
  Timestamp departure_date = flight_get_real_departure_date(flight);
  char *destination_airport_id = flight_get_destination(flight);
  Timestamp arrival_date = flight_get_real_arrival_date(flight);
  insert_passenger_by_airport_by_year(airports_catalog, origin_airport_id,
                                      departure_date.date / 10000);
  insert_passenger_by_airport_by_year(airports_catalog, destination_airport_id,
                                      arrival_date.date / 10000);
  g_free(origin_airport_id);
  g_free(destination_airport_id);
}