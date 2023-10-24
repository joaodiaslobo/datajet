#include "data/database.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

#include "data/catalogs/catalog_flight.h"
#include "data/catalogs/catalog_passenger.h"
#include "data/catalogs/catalog_reservation.h"
#include "data/catalogs/catalog_user.h"
#include "data/schemas/flight.h"
#include "data/schemas/passenger.h"
#include "data/schemas/user.h"
#include "io/file.h"
#include "io/parsing/parser.h"

struct database {
  CatalogUser *userCatalog;
  CatalogFlight *flightCatalog;
  CatalogPassenger *passengerCatalog;
  CatalogReservation *reservationCatalog;
};

Database *initialize_database() {
  Database *database = malloc(sizeof(struct database));

  database->userCatalog = initialize_users_catalog();
  database->flightCatalog = initialize_flights_catalog();
  database->reservationCatalog = initialize_reservations_catalog();
  database->passengerCatalog = initialize_passengers_catalog();

  return database;
}

void free_database(Database *database) {
  free_users_catalog(database->userCatalog);
  free_flights_catalog(database->flightCatalog);
  free_reservations_catalog(database->reservationCatalog);
  free_passengers_catalog(database->passengerCatalog);
  free(database);
}

int csv_populate_database(Database *database, char *csv_dataset_path) {
  /* Load users csv dataset */

  char *users_csv_path = build_full_file_path(csv_dataset_path, "users.csv");
  FILE *users_file = open_file(users_csv_path);

  read_csv(users_file, parse_user_and_add_to_catalog, database->userCatalog);

  close_file(users_file);
  free(users_csv_path);

  /* Load flights csv dataset */

  char *flights_csv_path =
      build_full_file_path(csv_dataset_path, "flights.csv");
  FILE *flights_file = open_file(flights_csv_path);

  read_csv(flights_file, parse_flight_and_add_to_catalog,
           database->flightCatalog);

  close_file(flights_file);
  free(flights_csv_path);

  /* Load reservations csv dataset */

  char *reservations_csv_path =
      build_full_file_path(csv_dataset_path, "reservations.csv");
  FILE *reservations_file = open_file(reservations_csv_path);

  read_csv(reservations_file, parse_reservation_and_add_to_catalog,
           database->reservationCatalog);

  close_file(reservations_file);
  free(reservations_csv_path);

  /* Load passengers csv dataset */

  char *passengers_csv_path =
      build_full_file_path(csv_dataset_path, "passengers.csv");
  FILE *passengers_file = open_file(passengers_csv_path);

  read_csv(passengers_file, parse_passenger_and_add_to_catalog,
           database->passengerCatalog);

  close_file(passengers_file);
  free(passengers_csv_path);

  return 0;
}

CatalogUser *database_get_user_catalog(Database *database) {
  return database->userCatalog;
}

CatalogFlight *database_get_flight_catalog(Database *database) {
  return database->flightCatalog;
}

CatalogPassenger *database_get_passenger_catalog(Database *database) {
  return database->passengerCatalog;
}

CatalogReservation *database_get_reservation_catalog(Database *database) {
  return database->reservationCatalog;
}