#include "workers/batch.h"

#include <stdio.h>

#include "data/database.h"

// DEBUG PRINTS
#include "data/catalogs/catalog_flight.h"
#include "data/catalogs/catalog_passenger.h"
#include "data/catalogs/catalog_reservation.h"
#include "data/catalogs/catalog_user.h"
#include "data/schemas/flight.h"
#include "data/schemas/passenger.h"
#include "data/schemas/reservation.h"
#include "data/schemas/user.h"

int batch_worker(char **argv, Database *database) {
  printf("== BATCH MODE ==\n");
  char *dataset_folder_path = argv[0];
  // char *output_folder_path = argv[1];

  csv_populate_database(database, dataset_folder_path);

  /*
  CatalogUser *userCatalog = database_get_user_catalog(database);
  CatalogFlight *flightCatalog = database_get_flight_catalog(database);
  CatalogReservation *reservationCatalog =
      database_get_reservation_catalog(database);

  // DEBUG PRINTS
  int user_count = count_users(userCatalog);
  printf("== USERS (%d) ==\n", user_count);

  for (int i = 0; i < user_count; i++) {
    User *user = catalog_get_user_by_id(userCatalog, i);
    printf("ID: %s  Name: %s  Email: %s  Phone Number: %s  Country: %s\n",
           user_get_id(user), user_get_name(user), user_get_email(user),
           user_get_phone_number(user), user_country_code(user));
  }

  int flight_count = count_flights(flightCatalog);
  printf("\n== FLIGHTS (%d) ==\n", flight_count);

  for (int i = 0; i < flight_count; i++) {
    Flight *flight = catalog_get_flight_by_id(flightCatalog, i);
    printf("ID: %s  Airline: %s  Plane Model: %s  Total Seats: %d\n",
           flight_get_id(flight), flight_get_airline(flight),
           flight_get_plane_model(flight), flight_get_total_seats(flight));
  }

  int reservation_count = count_reservations(reservationCatalog);
  printf("\n== RESERVATIONS (%d) ==\n", reservation_count);

  for (int i = 0; i < reservation_count; i++) {
    Reservation *reservation =
        catalog_get_reservation_by_id(reservationCatalog, i);
    printf("ID: %s  Hotel Name: %s Hotel Stars: %d  Price p/Night: %d\n",
           reservation_get_id(reservation),
           reservation_get_hotel_name(reservation),
           reservation_get_hotel_stars(reservation),
           reservation_get_price_per_night(reservation));
  }

  int passenger_count =
      count_passengers(database_get_passenger_catalog(database));
  printf("\n== PASSENGERS (%d) ==\n", passenger_count);

  for (int i = 0; i < passenger_count; i++) {
    Passenger *passenger = catalog_get_passenger_by_id(
        database_get_passenger_catalog(database), i);
    printf("Flight ID: %s User ID: %s\n", passenger_get_flight_id(passenger),
           passenger_get_user_id(passenger));
  }

  printf("\n== FREEING DATA ==\n");
  */

  return 0;
}