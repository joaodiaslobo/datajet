#ifndef CATALOG_FLIGHT_H
#define CATALOG_FLIGHT_H

#include <glib.h>

#include "data/schemas/flight.h"

typedef struct catalogFlight CatalogFlight;

CatalogFlight *initialize_flights_catalog();

void free_flights_catalog(CatalogFlight *catalog);

void insert_flight(CatalogFlight *catalog, Flight *flight, gpointer key);

int count_flights(CatalogFlight *catalog);

void remove_flight(CatalogFlight *catalog, int flight_id);

void foreach_flight_remove(CatalogFlight *catalog, GHRFunc function,
                           void *data);

bool flight_exists(CatalogFlight *catalog, int flight_id);

Flight *catalog_get_flight_by_id(CatalogFlight *catalog, int flight_id);

int compare_flights_array_elements_by_schedule_departure_date(gpointer a,
                                                              gpointer b);

GPtrArray *get_flights_array(CatalogFlight *catalog);

#endif