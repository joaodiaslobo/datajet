#include "data/catalogs/catalog_reservation.h"

#include <glib.h>
#include <stdlib.h>

#include "data/procedures/aggregates.h"
#include "data/schemas/reservation.h"
#include "data/schemas/user.h"

struct catalogReservation {
  GHashTable *reservations;
  GHashTable *user_reservations;
  GHashTable *hotel_reservations;
  GHashTable *date_reservations_aggregate;
};

CatalogReservation *initialize_reservations_catalog() {
  CatalogReservation *catalog = malloc(sizeof(struct catalogReservation));
  catalog->reservations =
      g_hash_table_new_full(NULL, g_direct_equal, NULL, free_reservation);
  catalog->user_reservations = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, free_reservation_ptr_array);
  catalog->hotel_reservations = g_hash_table_new_full(
      NULL, g_direct_equal, NULL, free_reservation_ptr_array);
  catalog->date_reservations_aggregate =
      g_hash_table_new_full(NULL, g_direct_equal, NULL, free);

  return catalog;
}

void free_reservation_ptr_array(void *array) { g_ptr_array_free(array, TRUE); }

void free_reservations_catalog(CatalogReservation *catalog) {
  g_hash_table_destroy(catalog->user_reservations);
  g_hash_table_destroy(catalog->hotel_reservations);
  g_hash_table_destroy(catalog->reservations);
  g_hash_table_destroy(catalog->date_reservations_aggregate);

  free(catalog);
}

void insert_reservation(CatalogReservation *catalog, Reservation *reservation,
                        gpointer key) {
  g_hash_table_insert(catalog->reservations, key, reservation);

  /* Insert reservation into user reservations association Hash Table */
  char *user_id_key = reservation_get_user_id(reservation);
  GPtrArray *user_reservations =
      g_hash_table_lookup(catalog->user_reservations, user_id_key);
  if (user_reservations == NULL) {
    user_reservations = g_ptr_array_new();
    g_hash_table_insert(catalog->user_reservations, user_id_key,
                        user_reservations);
  } else {
    g_free(user_id_key);
  }

  g_ptr_array_add(user_reservations, reservation);

  /* Insert reservation into hotel reservations association Hash Table */
  gpointer hotel_id_key =
      GUINT_TO_POINTER(reservation_get_hotel_id(reservation));
  GPtrArray *hotel_reservations =
      g_hash_table_lookup(catalog->hotel_reservations, hotel_id_key);
  if (hotel_reservations == NULL) {
    hotel_reservations = g_ptr_array_new();
    g_hash_table_insert(catalog->hotel_reservations, hotel_id_key,
                        hotel_reservations);
  }

  g_ptr_array_add(hotel_reservations, reservation);

  increment_reservations_date_aggregate(
      catalog, reservation_get_begin_date(reservation));
}

void increment_reservations_date_aggregate(CatalogReservation *catalog,
                                           Timestamp begin_date) {
  increment_entity_aggregate(catalog->date_reservations_aggregate,
                             begin_date.date);
  increment_entity_aggregate(catalog->date_reservations_aggregate,
                             begin_date.date / 100);
  increment_entity_aggregate(catalog->date_reservations_aggregate,
                             begin_date.date / 10000);
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

GPtrArray *get_hotel_reservations(CatalogReservation *catalog,
                                  unsigned short hotel_id) {
  return g_hash_table_lookup(catalog->hotel_reservations,
                             GUINT_TO_POINTER(hotel_id));
}

GPtrArray *get_user_reservations(CatalogReservation *catalog, char *user_id) {
  return g_hash_table_lookup(catalog->user_reservations, user_id);
}

Reservation *catalog_get_reservation_by_id(CatalogReservation *catalog,
                                           unsigned int reservation_id) {
  return g_hash_table_lookup(catalog->reservations,
                             GUINT_TO_POINTER(reservation_id));
}

int catalog_get_reservation_count_by_timestamp_key(CatalogReservation *catalog,
                                                   int timestamp_key) {
  int *count = g_hash_table_lookup(catalog->date_reservations_aggregate,
                                   GINT_TO_POINTER(timestamp_key));
  if (count == NULL) return 0;
  return *count;
}

int compare_reservations_array_elements_by_begin_date(gpointer a, gpointer b) {
  Reservation *reservation_a = *(Reservation **)a;
  Reservation *reservation_b = *(Reservation **)b;

  Timestamp begin_date_a = reservation_get_begin_date(reservation_a);
  Timestamp begin_date_b = reservation_get_begin_date(reservation_b);

  if (begin_date_a.date > begin_date_b.date) return -1;
  if (begin_date_a.date < begin_date_b.date) return 1;

  return 0;
}
