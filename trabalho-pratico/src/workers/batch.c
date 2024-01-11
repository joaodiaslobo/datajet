#include "workers/batch.h"

#include <stdio.h>

#include "data/catalogs/catalog_flight.h"
#include "data/catalogs/catalog_passenger.h"
#include "data/catalogs/catalog_reservation.h"
#include "data/catalogs/catalog_user.h"
#include "data/database.h"
#include "data/schemas/flight.h"
#include "data/schemas/passenger.h"
#include "data/schemas/reservation.h"
#include "data/schemas/user.h"
#include "io/interpreter.h"

int batch_worker(char **argv, Database *database) {
  printf("== BATCH MODE ==\n");
  char *dataset_folder_path = argv[0];
  char *query_commands_path = argv[1];

  printf("== POPULATING DATABASE ==\n");
  csv_populate_database(database, dataset_folder_path);

  CatalogUser *userCatalog = database_get_user_catalog(database);
  CatalogFlight *flightCatalog = database_get_flight_catalog(database);
  CatalogReservation *reservationCatalog =
      database_get_reservation_catalog(database);

  int user_count = count_users(userCatalog);
  printf("== USERS (%d) ==\n", user_count);

  int flight_count = count_flights(flightCatalog);
  printf("\n== FLIGHTS (%d) ==\n", flight_count);

  int reservation_count = count_reservations(reservationCatalog);
  printf("\n== RESERVATIONS (%d) ==\n", reservation_count);

  int passenger_count =
      count_passengers(database_get_passenger_catalog(database));
  printf("\n== PASSENGERS (%d) ==\n", passenger_count);

  printf("\n== EXECUTING QUERY COMMANDS ==\n");

  parse_and_execute_commands(query_commands_path, database);

  printf("\n== FREEING DATA ==\n");
  return 0;
}