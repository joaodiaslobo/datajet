#include "data/catalogs/catalog_airport.h"

#include <glib.h>
#include <stdlib.h>

#include "data/procedures/aggregates.h"
#include "data/procedures/sorting.h"
#include "data/schemas/flight.h"

struct catalogAirport {
  GHashTable *airports;
  GPtrArray *airport_delays;
  GHashTable *airport_passengers_by_year;
};

struct airportData {
  GPtrArray *delays;
  GHashTable *passengers_by_year;
};

struct airportPassengersByYear {
  char *airport_id;
  int *passengers;
};

struct airportDelayMedian {
  char *airport_id;
  int *delay_median;
};

CatalogAirport *initialize_airports_catalog() {
  CatalogAirport *catalog = malloc(sizeof(struct catalogAirport));
  catalog->airports = g_hash_table_new_full(g_str_hash, g_str_equal, NULL,
                                            (GDestroyNotify)free_airport_data);
  return catalog;
}

void free_airport_data(AirportData *data) {
  g_ptr_array_free(data->delays, TRUE);
  g_hash_table_destroy(data->passengers_by_year);
  free(data);
}

void free_airport_median(AirportDelayMedian *airport) {
  g_free(airport->airport_id);
  free(airport->delay_median);
  free(airport);
}

void free_airport_passengers_by_year(AirportPassengersByYear *airport) {
  free(airport->passengers);
  free(airport);
}

void free_airport_year_passengers_ptr_array(void *array) {
  g_ptr_array_free(array, TRUE);
}

void insert_airport_delay(CatalogAirport *catalog, char *airport_id,
                          int delay) {
  if (!g_hash_table_contains(catalog->airports, airport_id)) {
    insert_airport(catalog, airport_id);
  }
  AirportData *airport_data =
      g_hash_table_lookup(catalog->airports, airport_id);
  int *delay_ptr = malloc(sizeof(int));
  *delay_ptr = delay;
  g_ptr_array_add(airport_data->delays, delay_ptr);
}

void insert_airport(CatalogAirport *catalog, char *airport_id) {
  AirportData *data = malloc(sizeof(struct airportData));
  data->delays = g_ptr_array_new_with_free_func(free);
  data->passengers_by_year =
      g_hash_table_new_full(NULL, g_direct_equal, NULL, NULL);
  g_hash_table_insert(catalog->airports, g_strdup(airport_id), data);
}

void free_airports_catalog(CatalogAirport *catalog) {
  if (catalog->airport_delays != NULL)
    g_ptr_array_free(catalog->airport_delays, TRUE);
  if (catalog->airport_passengers_by_year != NULL)
    g_hash_table_destroy(catalog->airport_passengers_by_year);
  free(catalog);
}

void insert_passenger_by_airport_by_year(CatalogAirport *catalog,
                                         char *airport_id, int year) {
  if (!g_hash_table_contains(catalog->airports, airport_id)) {
    insert_airport(catalog, airport_id);
  }
  AirportData *airport_data =
      g_hash_table_lookup(catalog->airports, airport_id);
  if (!g_hash_table_contains(airport_data->passengers_by_year,
                             GINT_TO_POINTER(year))) {
    int *passengers_ptr = malloc(sizeof(int));
    *passengers_ptr = 1;
    g_hash_table_insert(airport_data->passengers_by_year, GINT_TO_POINTER(year),
                        passengers_ptr);
  } else {
    int *passengers_ptr = g_hash_table_lookup(airport_data->passengers_by_year,
                                              GINT_TO_POINTER(year));
    *passengers_ptr += 1;
  }
}

void catalog_airport_organize_data(CatalogAirport *catalog) {
  GHashTableIter iter;
  g_hash_table_iter_init(&iter, catalog->airports);
  char *airport_id = NULL;
  AirportData *airport_data = NULL;
  catalog->airport_delays =
      g_ptr_array_new_with_free_func((GDestroyNotify)free_airport_median);
  catalog->airport_passengers_by_year = g_hash_table_new_full(
      NULL, g_direct_equal, NULL,
      (GDestroyNotify)free_airport_year_passengers_ptr_array);
  while (g_hash_table_iter_next(&iter, (gpointer *)&airport_id,
                                (gpointer *)&airport_data)) {
    if (airport_data->delays->len != 0) {
      qsort_g_ptr_array(airport_data->delays, (GCompareFunc)compare_delays);
      int *median;
      if (airport_data->delays->len % 2 == 0) {
        int v1 = *(int *)g_ptr_array_index(airport_data->delays,
                                           airport_data->delays->len / 2);
        int v2 = *(int *)g_ptr_array_index(airport_data->delays,
                                           airport_data->delays->len / 2 - 1);
        median = malloc(sizeof(int));
        *median = (v1 + v2) / 2;
      } else {
        int v = *(int *)g_ptr_array_index(airport_data->delays,
                                          airport_data->delays->len / 2);
        median = malloc(sizeof(int));
        *median = v;
      }

      AirportDelayMedian *airportMedian =
          malloc(sizeof(struct airportDelayMedian));
      airportMedian->airport_id = airport_id;
      airportMedian->delay_median = median;
      g_ptr_array_add(catalog->airport_delays, airportMedian);
    } else {
      AirportDelayMedian *airportMedian =
          malloc(sizeof(struct airportDelayMedian));
      airportMedian->airport_id = airport_id;
      airportMedian->delay_median = malloc(sizeof(int));
      *(airportMedian->delay_median) = -1;
      g_ptr_array_add(catalog->airport_delays, airportMedian);
    }

    GHashTableIter iter_year;
    g_hash_table_iter_init(&iter_year, airport_data->passengers_by_year);
    gpointer year = NULL;
    int *passengers = NULL;

    while (g_hash_table_iter_next(&iter_year, (gpointer *)&year,
                                  (gpointer *)&passengers)) {
      GPtrArray *airport_passengers_by_year =
          g_hash_table_lookup(catalog->airport_passengers_by_year, year);
      if (airport_passengers_by_year == NULL) {
        airport_passengers_by_year = g_ptr_array_new_with_free_func(
            (GDestroyNotify)free_airport_passengers_by_year);
        g_hash_table_insert(catalog->airport_passengers_by_year, year,
                            airport_passengers_by_year);
      }
      AirportPassengersByYear *airport_passengers =
          malloc(sizeof(struct airportPassengersByYear));
      airport_passengers->airport_id = airport_id;
      airport_passengers->passengers = passengers;

      g_ptr_array_add(airport_passengers_by_year, airport_passengers);
    }
  }
  GHashTableIter iter_year;
  GPtrArray *airports_list = NULL;
  g_hash_table_iter_init(&iter_year, catalog->airport_passengers_by_year);

  while (g_hash_table_iter_next(&iter_year, NULL, (gpointer *)&airports_list)) {
    qsort_g_ptr_array(airports_list, (GCompareFunc)compare_passengers);
  }

  qsort_g_ptr_array(catalog->airport_delays, (GCompareFunc)compare_medians);
  g_hash_table_destroy(catalog->airports);
}

int compare_delays(gpointer a, gpointer b) {
  int *delay_a = *(int **)a;
  int *delay_b = *(int **)b;

  if (*delay_a < *delay_b) return -1;
  if (*delay_a > *delay_b) return 1;

  return 0;
}

int compare_medians(gpointer a, gpointer b) {
  AirportDelayMedian *airport_a = *(AirportDelayMedian **)a;
  AirportDelayMedian *airport_b = *(AirportDelayMedian **)b;

  if (*(airport_a->delay_median) == -1) return 1;
  if (*(airport_b->delay_median) == -1) return -1;

  if (*(airport_a->delay_median) > *(airport_b->delay_median)) return -1;
  if (*(airport_a->delay_median) < *(airport_b->delay_median)) return 1;

  if (strcmp(airport_a->airport_id, airport_b->airport_id) < 0) return -1;

  return 1;
}

int compare_passengers(gpointer a, gpointer b) {
  AirportPassengersByYear *airport_a = *(AirportPassengersByYear **)a;
  AirportPassengersByYear *airport_b = *(AirportPassengersByYear **)b;

  if (*(airport_a->passengers) > *(airport_b->passengers)) return -1;
  if (*(airport_a->passengers) < *(airport_b->passengers)) return 1;

  if (strcmp(airport_a->airport_id, airport_b->airport_id) < 0) return -1;

  return 1;
}

char *airport_delay_median_get_airport_id(AirportDelayMedian *airport) {
  return g_strdup(airport->airport_id);
}

int airport_delay_median_get_delay_median(AirportDelayMedian *airport) {
  return *airport->delay_median;
}

GPtrArray *catalog_get_airport_delays(CatalogAirport *catalog) {
  return catalog->airport_delays;
}

char *airport_passengers_by_year_get_airport_id(
    AirportPassengersByYear *airport) {
  return g_strdup(airport->airport_id);
}

int airport_passengers_by_year_get_passengers(
    AirportPassengersByYear *airport) {
  return *airport->passengers;
}

GHashTable *catalog_get_airport_passengers_by_year(CatalogAirport *catalog) {
  return catalog->airport_passengers_by_year;
}