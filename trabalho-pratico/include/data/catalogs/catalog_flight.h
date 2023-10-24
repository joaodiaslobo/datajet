#ifndef CATALOG_FLIGHT_H
#define CATALOG_FLIGHT_H

#include <glib.h>

#include "data/schemas/flight.h"

typedef struct catalogFlight CatalogFlight;

CatalogFlight *initialize_flights_catalog();

void free_flights_catalog(CatalogFlight *catalog);

void insert_flight(CatalogFlight *catalog, Flight *flight);

int count_flights(CatalogFlight *catalog);

Flight *catalog_get_flight_by_id(CatalogFlight *catalog, int flight_id);

#endif