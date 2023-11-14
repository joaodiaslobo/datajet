#include "data/catalogs/catalog_flight.h"

#include <glib.h>

#include "data/schemas/flight.h"

struct catalogFlight {
  GHashTable *flights;
};

CatalogFlight *initialize_flights_catalog() {
  CatalogFlight *catalog = malloc(sizeof(struct catalogFlight));
  catalog->flights =
      g_hash_table_new_full(NULL, g_direct_equal, NULL, free_flight);

  return catalog;
}

void free_flights_catalog(CatalogFlight *catalog) {
  g_hash_table_destroy(catalog->flights);

  free(catalog);
}

void insert_flight(CatalogFlight *catalog, Flight *flight, gpointer key) {
  g_hash_table_insert(catalog->flights, key, flight);
}

void remove_flight(CatalogFlight *catalog, int flight_id) {
  g_hash_table_remove(catalog->flights, GINT_TO_POINTER(flight_id));
}

void foreach_flight_remove(CatalogFlight *catalog, GHRFunc function,
                           void *data) {
  g_hash_table_foreach_remove(catalog->flights, function, data);
}

bool flight_exists(CatalogFlight *catalog, int flight_id) {
  return g_hash_table_contains(catalog->flights, GINT_TO_POINTER(flight_id));
}

int count_flights(CatalogFlight *catalog) {
  return g_hash_table_size(catalog->flights);
}

Flight *catalog_get_flight_by_id(CatalogFlight *catalog, int flight_id) {
  return g_hash_table_lookup(catalog->flights, GINT_TO_POINTER(flight_id));
}