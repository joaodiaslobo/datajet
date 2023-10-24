#ifndef CATALOG_PASSENGER_H
#define CATALOG_PASSENGER_H

#include <glib.h>

#include "data/schemas/passenger.h"

typedef struct catalogPassenger CatalogPassenger;

CatalogPassenger *initialize_passengers_catalog();

void free_passengers_catalog(CatalogPassenger *catalog);

void insert_passenger(CatalogPassenger *catalog, Passenger *passenger);

int count_passengers(CatalogPassenger *catalog);

Passenger *catalog_get_passenger_by_id(CatalogPassenger *catalog,
                                       int passenger_id);

#endif