#include "data/catalogs/catalog_passenger.h"

#include <glib.h>

#include "data/schemas/passenger.h"

struct catalogPassenger {
  GPtrArray *passengers;
};

CatalogPassenger *initialize_passengers_catalog() {
  CatalogPassenger *catalog = malloc(sizeof(struct catalogPassenger));
  catalog->passengers = g_ptr_array_new();

  return catalog;
}

void free_passengers_catalog(CatalogPassenger *catalog) {
  for (unsigned int i = 0; i < catalog->passengers->len; i++) {
    free_passenger((Passenger *)catalog->passengers->pdata[i]);
  }

  g_ptr_array_free(catalog->passengers, FALSE);

  free(catalog);
}

void insert_passenger(CatalogPassenger *catalog, Passenger *passenger) {
  g_ptr_array_add(catalog->passengers, passenger);
}

int count_passengers(CatalogPassenger *catalog) {
  return catalog->passengers->len;
}

Passenger *catalog_get_passenger_by_id(CatalogPassenger *catalog,
                                       int passenger_id) {
  return (Passenger *)catalog->passengers->pdata[passenger_id];
}