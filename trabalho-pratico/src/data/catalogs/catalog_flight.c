#include "data/catalogs/catalog_flight.h"

#include "data/schemas/flight.h"

struct catalogFlight {
  GPtrArray *flights;
};

CatalogFlight *initialize_flights_catalog() {
  CatalogFlight *catalog = malloc(sizeof(struct catalogFlight));
  catalog->flights = g_ptr_array_new();

  return catalog;
}

void free_flights_catalog(CatalogFlight *catalog) {
  for (unsigned int i = 0; i < catalog->flights->len; i++) {
    free_flight((Flight *)catalog->flights->pdata[i]);
  }

  g_ptr_array_free(catalog->flights, FALSE);

  free(catalog);
}

void insert_flight(CatalogFlight *catalog, Flight *flight) {
  g_ptr_array_add(catalog->flights, flight);
}

int count_flights(CatalogFlight *catalog) { return catalog->flights->len; }

Flight *catalog_get_flight_by_id(CatalogFlight *catalog, int flight_id) {
  return (Flight *)catalog->flights->pdata[flight_id];
}