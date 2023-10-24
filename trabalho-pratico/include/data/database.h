#ifndef DATABASE_H
#define DATABASE_H

#include "catalogs/catalog_flight.h"
#include "catalogs/catalog_passenger.h"
#include "catalogs/catalog_reservation.h"
#include "catalogs/catalog_user.h"

typedef struct database Database;

Database *initialize_database();

void free_database(Database *database);

int csv_populate_database(Database *database, char *csv_dataset_path);

CatalogUser *database_get_user_catalog(Database *database);

CatalogFlight *database_get_flight_catalog(Database *database);

CatalogPassenger *database_get_passenger_catalog(Database *database);

CatalogReservation *database_get_reservation_catalog(Database *database);

#endif