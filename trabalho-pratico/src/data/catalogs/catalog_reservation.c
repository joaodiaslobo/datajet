#include "data/catalogs/catalog_reservation.h"

#include <glib.h>

#include "data/schemas/reservation.h"

struct catalogReservation {
  GHashTable *reservations;
  GHashTable *user_reservations;
};

CatalogReservation *initialize_reservations_catalog() {
  CatalogReservation *catalog = malloc(sizeof(struct catalogReservation));
  catalog->reservations =
      g_hash_table_new_full(NULL, g_direct_equal, NULL, free_reservation);
  catalog->user_reservations = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, free_reservation_ptr_array);

  return catalog;
}

void free_reservation_ptr_array(void *array) { g_ptr_array_free(array, TRUE); }

void free_reservations_catalog(CatalogReservation *catalog) {
  g_hash_table_destroy(catalog->user_reservations);
  g_hash_table_destroy(catalog->reservations);

  free(catalog);
}

void insert_reservation(CatalogReservation *catalog, Reservation *reservation,
                        gpointer key) {
  g_hash_table_insert(catalog->reservations, key, reservation);
  char *user_id_key = reservation_get_user_id(reservation);
  GPtrArray *reservations =
      g_hash_table_lookup(catalog->user_reservations, user_id_key);
  if (reservations == NULL) {
    reservations = g_ptr_array_new();
    g_hash_table_insert(catalog->user_reservations, user_id_key, reservations);
  } else {
    g_free(user_id_key);
  }

  g_ptr_array_add(reservations, reservation);
}

int count_reservations(CatalogReservation *catalog) {
  return g_hash_table_size(catalog->reservations);
}

int count_user_reservations(CatalogReservation *catalog, char *user_id) {
  GPtrArray *reservations =
      g_hash_table_lookup(catalog->user_reservations, user_id);
  if (reservations == NULL) {
    return 0;
  }

  return reservations->len;
}

Reservation *get_user_reservation_by_index(CatalogReservation *catalog,
                                           char *user_id, int index) {
  GPtrArray *reservations =
      g_hash_table_lookup(catalog->user_reservations, user_id);
  if (reservations == NULL) {
    return NULL;
  }

  return g_ptr_array_index(reservations, index);
}

Reservation *catalog_get_reservation_by_id(CatalogReservation *catalog,
                                           int reservation_id) {
  return g_hash_table_lookup(catalog->reservations,
                             GINT_TO_POINTER(reservation_id));
}