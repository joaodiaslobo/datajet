#include "data/catalogs/catalog_passenger.h"

#include <glib.h>

#include "data/schemas/passenger.h"

struct catalogPassenger {
  GPtrArray *passengers;
};

CatalogPassenger *initialize_passengers_catalog() {
  CatalogPassenger *catalog = malloc(sizeof(struct catalogPassenger));
  catalog->passengers = g_ptr_array_new_with_free_func(free_passenger);

  return catalog;
}

void free_passengers_catalog(CatalogPassenger *catalog) {
  g_ptr_array_free(catalog->passengers, TRUE);

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