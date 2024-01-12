#include "data/catalogs/catalog_passenger.h"

#include <glib.h>
#include <stdlib.h>

#include "data/procedures/aggregates.h"
#include "data/schemas/flight.h"
#include "data/schemas/passenger.h"
#include "data/schemas/schema_data_types.h"

struct catalogPassenger {
  GHashTable *flight_users;
  GHashTable *user_flights;
  int count;
  GHashTable *date_passengers_aggregate;
  GHashTable *date_unique_passengers_aggregate;
};

CatalogPassenger *initialize_passengers_catalog() {
  CatalogPassenger *catalog = malloc(sizeof(struct catalogPassenger));
  catalog->flight_users =
      g_hash_table_new_full(NULL, g_direct_equal, NULL, free_ptr_array);
  catalog->user_flights =
      g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_ptr_array);
  catalog->count = 0;
  catalog->date_passengers_aggregate =
      g_hash_table_new_full(NULL, g_direct_equal, NULL, free);
  catalog->date_unique_passengers_aggregate =
      g_hash_table_new_full(NULL, g_direct_equal, NULL, free_hash_table);
  return catalog;
}

void free_ptr_array(void *array) { g_ptr_array_free(array, TRUE); }

void free_hash_table(void *hash_table) { g_hash_table_destroy(hash_table); }

void free_passengers_catalog(CatalogPassenger *catalog) {
  g_hash_table_destroy(catalog->flight_users);
  g_hash_table_destroy(catalog->user_flights);
  g_hash_table_destroy(catalog->date_passengers_aggregate);
  g_hash_table_destroy(catalog->date_unique_passengers_aggregate);

  free(catalog);
}

void insert_passenger(CatalogPassenger *catalog, unsigned int flight_id,
                      char *user_id_unsafe, void *flight, void *user) {
  char *user_id = g_strdup(user_id_unsafe);
  GPtrArray *users =
      g_hash_table_lookup(catalog->flight_users, GUINT_TO_POINTER(flight_id));
  if (users == NULL) {
    users = g_ptr_array_new();
    g_hash_table_insert(catalog->flight_users, GUINT_TO_POINTER(flight_id),
                        users);
  }
  g_ptr_array_add(users, user);

  GPtrArray *flights;
  char *username;
  /*
   * This saves us a lot of memory usage by reusing the same string for the
   * user_id on the flights associations and the unique passengers aggregate.
   */
  bool has_found =
      g_hash_table_lookup_extended(catalog->user_flights, user_id,
                                   (gpointer *)&username, (gpointer *)&flights);
  if (!has_found) {
    flights = g_ptr_array_new();
    g_hash_table_insert(catalog->user_flights, user_id, flights);
    username = user_id;
  } else {
    g_free(user_id);
  }
  g_ptr_array_add(flights, flight);
  catalog->count++;

  increment_passengers_date_aggregate(
      catalog, flight_get_schedule_departure_date(flight));

  increment_unique_passengers_date_aggregate(
      catalog, flight_get_schedule_departure_date(flight), username);
}

void increment_passengers_date_aggregate(CatalogPassenger *catalog,
                                         Timestamp schedule_departure_date) {
  increment_entity_aggregate(catalog->date_passengers_aggregate,
                             schedule_departure_date.date);
  increment_entity_aggregate(catalog->date_passengers_aggregate,
                             schedule_departure_date.date / 100);
  increment_entity_aggregate(catalog->date_passengers_aggregate,
                             schedule_departure_date.date / 10000);
}

void increment_unique_passengers_date_aggregate(
    CatalogPassenger *catalog, Timestamp schedule_departure_date,
    char *user_id) {
  increment_hash_aggregate(catalog->date_unique_passengers_aggregate,
                           schedule_departure_date.date, user_id);
  increment_hash_aggregate(catalog->date_unique_passengers_aggregate,
                           schedule_departure_date.date / 100, user_id);
  increment_hash_aggregate(catalog->date_unique_passengers_aggregate,
                           schedule_departure_date.date / 10000, user_id);
}

void increment_hash_aggregate(GHashTable *hash_table,
                              unsigned int timestamp_key, char *user_id) {
  if (user_id == NULL) return;
  GHashTable *table =
      g_hash_table_lookup(hash_table, GUINT_TO_POINTER(timestamp_key));
  if (table == NULL) {
    table = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
    g_hash_table_insert(hash_table, GUINT_TO_POINTER(timestamp_key), table);
  }

  g_hash_table_insert(table, user_id, NULL);
}

void remove_passengers_by_user_id(CatalogPassenger *catalog, char *user_id) {
  GPtrArray *flights = g_hash_table_lookup(catalog->user_flights, user_id);
  if (flights == NULL) {
    return;
  }

  for (int i = 0; i < (int)flights->len; i++) {
    unsigned int flight_id = GPOINTER_TO_UINT(flights->pdata[i]);
    GPtrArray *users =
        g_hash_table_lookup(catalog->flight_users, GUINT_TO_POINTER(flight_id));
    if (users == NULL) {
      continue;
    }

    for (int j = 0; j < (int)users->len; j++) {
      if (strcmp(user_id, users->pdata[j]) == 0) {
        g_ptr_array_remove_index(users, j);
        break;
      }
    }
  }

  g_hash_table_remove(catalog->user_flights, user_id);
  catalog->count--;
}

int count_flight_users(CatalogPassenger *catalog, unsigned int flight_id) {
  GPtrArray *users =
      g_hash_table_lookup(catalog->flight_users, GUINT_TO_POINTER(flight_id));
  if (users == NULL) {
    return 0;
  }

  return users->len;
}

int count_user_flights(CatalogPassenger *catalog, char *user_id) {
  GPtrArray *flights = g_hash_table_lookup(catalog->user_flights, user_id);
  if (flights == NULL) {
    return 0;
  }

  return flights->len;
}

int catalog_get_passenger_count_by_timestamp_key(CatalogPassenger *catalog,
                                                 int timestamp_key) {
  int *count = g_hash_table_lookup(catalog->date_passengers_aggregate,
                                   GINT_TO_POINTER(timestamp_key));
  if (count == NULL) return 0;
  return *count;
}

int catalog_get_unique_passenger_count_by_timestamp_key(
    CatalogPassenger *catalog, int timestamp_key) {
  GHashTable *table =
      g_hash_table_lookup(catalog->date_unique_passengers_aggregate,
                          GINT_TO_POINTER(timestamp_key));
  if (table == NULL) return 0;
  return g_hash_table_size(table);
}

void remove_passengers_by_flight_id(CatalogPassenger *catalog,
                                    unsigned int flight_id) {
  GPtrArray *users =
      g_hash_table_lookup(catalog->flight_users, GUINT_TO_POINTER(flight_id));
  if (users == NULL) {
    return;
  }
  for (int i = 0; i < (int)users->len; i++) {
    char *user_id = users->pdata[i];
    GPtrArray *flights = g_hash_table_lookup(catalog->user_flights, user_id);
    if (flights == NULL) {
      continue;
    }

    for (int j = 0; j < (int)flights->len; j++) {
      if (flight_id == GPOINTER_TO_UINT(flights->pdata[j])) {
        g_ptr_array_remove_index(flights, j);
        break;
      }
    }
  }

  g_hash_table_remove(catalog->flight_users, GUINT_TO_POINTER(flight_id));
  catalog->count--;
}

int count_passengers(CatalogPassenger *catalog) { return catalog->count; }

GPtrArray *get_user_flights(CatalogPassenger *catalog, char *user_id) {
  return g_hash_table_lookup(catalog->user_flights, user_id);
}