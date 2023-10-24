#include "data/catalogs/catalog_reservation.h"

#include <glib.h>

#include "data/schemas/reservation.h"

struct catalogReservation {
  GPtrArray *reservations;
};

CatalogReservation *initialize_reservations_catalog() {
  CatalogReservation *catalog = malloc(sizeof(struct catalogReservation));
  catalog->reservations = g_ptr_array_new();

  return catalog;
}

void free_reservations_catalog(CatalogReservation *catalog) {
  for (unsigned int i = 0; i < catalog->reservations->len; i++) {
    free_reservation((Reservation *)catalog->reservations->pdata[i]);
  }

  g_ptr_array_free(catalog->reservations, FALSE);

  free(catalog);
}

void insert_reservation(CatalogReservation *catalog, Reservation *reservation) {
  g_ptr_array_add(catalog->reservations, reservation);
}

int count_reservations(CatalogReservation *catalog) {
  return catalog->reservations->len;
}

Reservation *catalog_get_reservation_by_id(CatalogReservation *catalog,
                                           int reservation_id) {
  return (Reservation *)catalog->reservations->pdata[reservation_id];
}