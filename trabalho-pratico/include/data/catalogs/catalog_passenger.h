#ifndef CATALOG_PASSENGER_H
#define CATALOG_PASSENGER_H

#include <glib.h>

#include "data/schemas/passenger.h"

typedef struct catalogPassenger CatalogPassenger;

CatalogPassenger *initialize_passengers_catalog();

void free_ptr_array(void *array);

void free_passengers_catalog(CatalogPassenger *catalog);

void insert_passenger(CatalogPassenger *catalog, int flight_id,
                      char *user_id_unsafe, void *flight, void *user);

int count_flight_users(CatalogPassenger *catalog, int flight_id);

int count_user_flights(CatalogPassenger *catalog, char *user_id);

void remove_passengers_by_user_id(CatalogPassenger *catalog, char *user_id);

void remove_passengers_by_flight_id(CatalogPassenger *catalog, int flight_id);

int count_passengers(CatalogPassenger *catalog);

GPtrArray *get_user_flights(CatalogPassenger *catalog, char *user_id);

#endif