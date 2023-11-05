#include "data/catalogs/catalog_flight.h"

#include <glib.h>

#include "data/schemas/flight.h"

struct catalogFlight {
  GPtrArray *flights;
};

CatalogFlight *initialize_flights_catalog() {
  CatalogFlight *catalog = malloc(sizeof(struct catalogFlight));
  catalog->flights = g_ptr_array_new_with_free_func(free_flight);

  return catalog;
}

void free_flights_catalog(CatalogFlight *catalog) {
  g_ptr_array_free(catalog->flights, TRUE);

  free(catalog);
}

void insert_flight(CatalogFlight *catalog, Flight *flight) {
  g_ptr_array_add(catalog->flights, flight);
}

int count_flights(CatalogFlight *catalog) { return catalog->flights->len; }

Flight *catalog_get_flight_by_id(CatalogFlight *catalog, int flight_id) {
  return (Flight *)catalog->flights->pdata[flight_id];
}