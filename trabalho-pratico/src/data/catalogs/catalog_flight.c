#include "data/catalogs/catalog_flight.h"

#include <glib.h>
#include <stdlib.h>

#include "data/procedures/aggregates.h"
#include "data/procedures/sorting.h"
#include "data/schemas/flight.h"

struct catalogFlight {
  GHashTable *flights;
  GPtrArray *flight_array;
  bool flight_array_sorted;
  GHashTable *date_flights_aggregate;
};

CatalogFlight *initialize_flights_catalog() {
  CatalogFlight *catalog = malloc(sizeof(struct catalogFlight));
  catalog->flights =
      g_hash_table_new_full(NULL, g_direct_equal, NULL, free_flight);
  catalog->flight_array = g_ptr_array_new();
  catalog->flight_array_sorted = false;
  catalog->date_flights_aggregate =
      g_hash_table_new_full(NULL, g_direct_equal, NULL, free);

  return catalog;
}

void free_flights_catalog(CatalogFlight *catalog) {
  g_hash_table_destroy(catalog->flights);
  g_ptr_array_free(catalog->flight_array, TRUE);
  g_hash_table_destroy(catalog->date_flights_aggregate);

  free(catalog);
}

static bool have_flights_been_sorted(CatalogFlight *catalog) {
  return catalog->flight_array_sorted;
}

static void set_flights_sorting(CatalogFlight *catalog, bool value) {
  catalog->flight_array_sorted = value;
}

void insert_flight(CatalogFlight *catalog, Flight *flight, gpointer key) {
  g_hash_table_insert(catalog->flights, key, flight);
  g_ptr_array_add(catalog->flight_array, flight);
  set_flights_sorting(catalog, false);

  increment_flights_date_aggregate(catalog,
                                   flight_get_schedule_departure_date(flight));
}

void increment_flights_date_aggregate(CatalogFlight *catalog,
                                      Timestamp schedule_departure_date) {
  increment_entity_aggregate(catalog->date_flights_aggregate,
                             schedule_departure_date.date);
  increment_entity_aggregate(catalog->date_flights_aggregate,
                             schedule_departure_date.date / 100);
  increment_entity_aggregate(catalog->date_flights_aggregate,
                             schedule_departure_date.date / 10000);
}

int count_flights(CatalogFlight *catalog) {
  return g_hash_table_size(catalog->flights);
}

void remove_flight(CatalogFlight *catalog, unsigned int flight_id) {
  int flight_count = count_flights(catalog);
  int removed = 0;
  for (int i = 0; i < flight_count && !removed; i++) {
    Flight *flight = g_ptr_array_index(catalog->flight_array, i);
    unsigned int id = flight_get_id(flight);
    if (id == flight_id) {
      g_ptr_array_remove_index(catalog->flight_array, i);
    }
  }

  g_hash_table_remove(catalog->flights, GUINT_TO_POINTER(flight_id));
}

void foreach_flight_remove(CatalogFlight *catalog, GHRFunc function,
                           void *data) {
  g_hash_table_foreach_remove(catalog->flights, function, data);
}

bool flight_exists(CatalogFlight *catalog, unsigned int flight_id) {
  return g_hash_table_contains(catalog->flights, GUINT_TO_POINTER(flight_id));
}

Flight *catalog_get_flight_by_id(CatalogFlight *catalog,
                                 unsigned int flight_id) {
  return g_hash_table_lookup(catalog->flights, GUINT_TO_POINTER(flight_id));
}

void catalog_sort_flights_by_schedule_departure_date(CatalogFlight *catalog) {
  if (!have_flights_been_sorted(catalog)) {
    qsort_g_ptr_array(
        catalog->flight_array,
        (GCompareFunc)
            compare_flights_array_elements_by_schedule_departure_date);
    set_flights_sorting(catalog, true);
  }
}

int catalog_get_flight_count_by_timestamp_key(CatalogFlight *catalog,
                                              int timestamp_key) {
  int *count = g_hash_table_lookup(catalog->date_flights_aggregate,
                                   GINT_TO_POINTER(timestamp_key));
  if (count == NULL) return 0;
  return *count;
}

int compare_flights_array_elements_by_schedule_departure_date(gpointer a,
                                                              gpointer b) {
  Flight *flight_a = *(Flight **)a;
  Flight *flight_b = *(Flight **)b;

  Timestamp schedule_departure_date_a =
      flight_get_schedule_departure_date(flight_a);
  Timestamp schedule_departure_date_b =
      flight_get_schedule_departure_date(flight_b);

  if (schedule_departure_date_a.date > schedule_departure_date_b.date)
    return -1;
  if (schedule_departure_date_a.date < schedule_departure_date_b.date) return 1;
  if (schedule_departure_date_a.date == schedule_departure_date_b.date &&
      schedule_departure_date_a.time > schedule_departure_date_b.time)
    return -1;
  if (schedule_departure_date_a.date == schedule_departure_date_b.date &&
      schedule_departure_date_a.time < schedule_departure_date_b.time)
    return 1;
  return 0;
}

GPtrArray *get_flights_array(CatalogFlight *catalog) {
  return catalog->flight_array;
}