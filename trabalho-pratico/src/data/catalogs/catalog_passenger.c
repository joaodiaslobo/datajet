#include "data/catalogs/catalog_passenger.h"

#include <glib.h>

#include "data/schemas/passenger.h"

struct catalogPassenger {
  GHashTable *flight_users;
  GHashTable *user_flights;
  int count;
};

CatalogPassenger *initialize_passengers_catalog() {
  CatalogPassenger *catalog = malloc(sizeof(struct catalogPassenger));
  catalog->flight_users =
      g_hash_table_new_full(NULL, g_direct_equal, NULL, free_ptr_array);
  catalog->user_flights =
      g_hash_table_new_full(g_str_hash, g_str_equal, NULL, free_ptr_array);
  catalog->count = 0;

  return catalog;
}

void free_ptr_array(void *array) { g_ptr_array_free(array, TRUE); }

void free_passengers_catalog(CatalogPassenger *catalog) {
  g_hash_table_destroy(catalog->flight_users);
  g_hash_table_destroy(catalog->user_flights);

  free(catalog);
}

void insert_passenger(CatalogPassenger *catalog, int flight_id,
                      char *user_id_unsafe) {
  char *user_id = g_strdup(user_id_unsafe);
  GPtrArray *users =
      g_hash_table_lookup(catalog->flight_users, GINT_TO_POINTER(flight_id));
  if (users == NULL) {
    users = g_ptr_array_new_with_free_func(g_free);
    g_hash_table_insert(catalog->flight_users, GINT_TO_POINTER(flight_id),
                        users);
  }
  g_ptr_array_add(users, user_id);

  GPtrArray *flights = g_hash_table_lookup(catalog->user_flights, user_id);
  if (flights == NULL) {
    flights = g_ptr_array_new();
    g_hash_table_insert(catalog->user_flights, user_id, flights);
  }

  g_ptr_array_add(flights, GINT_TO_POINTER(flight_id));
  catalog->count++;
}

void remove_passengers_by_user_id(CatalogPassenger *catalog, char *user_id) {
  GPtrArray *flights = g_hash_table_lookup(catalog->user_flights, user_id);
  if (flights == NULL) {
    return;
  }

  for (int i = 0; i < (int)flights->len; i++) {
    int flight_id = GPOINTER_TO_INT(flights->pdata[i]);
    GPtrArray *users =
        g_hash_table_lookup(catalog->flight_users, GINT_TO_POINTER(flight_id));
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

int count_flight_users(CatalogPassenger *catalog, int flight_id) {
  GPtrArray *users =
      g_hash_table_lookup(catalog->flight_users, GINT_TO_POINTER(flight_id));
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

void remove_passengers_by_flight_id(CatalogPassenger *catalog, int flight_id) {
  GPtrArray *users =
      g_hash_table_lookup(catalog->flight_users, GINT_TO_POINTER(flight_id));
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
      if (flight_id == GPOINTER_TO_INT(flights->pdata[j])) {
        g_ptr_array_remove_index(flights, j);
        break;
      }
    }
  }

  g_hash_table_remove(catalog->flight_users, GINT_TO_POINTER(flight_id));
  catalog->count--;
}

int count_passengers(CatalogPassenger *catalog) { return catalog->count; }