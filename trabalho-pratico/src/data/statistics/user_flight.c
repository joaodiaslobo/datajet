#include "data/statistics/user_flight.h"

#include <stdbool.h>

#include "data/catalogs/catalog_flight.h"
#include "data/catalogs/catalog_user.h"
#include "data/database.h"

// Association via passengers catalog

void create_passenger_association(Database *database, char *user_id,
                                  unsigned int flight_id) {
  CatalogUser *users_catalog = database_get_user_catalog(database);
  CatalogFlight *flight_catalog = database_get_flight_catalog(database);

  User *user = catalog_get_user_by_id(users_catalog, user_id);
  if (user == NULL) return;
  Flight *flight = catalog_get_flight_by_id(flight_catalog, flight_id);
  if (flight == NULL) return;

  CatalogPassenger *passengers_catalog =
      database_get_passenger_catalog(database);
  insert_passenger(passengers_catalog, flight_id, user_id, (void *)flight,
                   (void *)user);
}

bool validate_passenger_association(Database *database, char *user_id,
                                    unsigned int flight_id) {
  // Checks if the user and flight exist
  CatalogUser *users_catalog = database_get_user_catalog(database);
  CatalogFlight *flight_catalog = database_get_flight_catalog(database);
  return user_exists(users_catalog, user_id) &&
         flight_exists(flight_catalog, flight_id);
}

bool validate_flight_passenger_count(gpointer key, Flight *flight,
                                     void *database) {
  int total_seats = (int)flight_get_total_seats(flight);
  unsigned int flight_id = GPOINTER_TO_UINT(key);
  CatalogPassenger *catalog = database_get_passenger_catalog(database);

  int actual_seats = count_flight_users(catalog, flight_id);

  if (actual_seats > total_seats) {
    remove_flight_passengers(database, flight_id);
    return true;
  }

  return false;
}

void remove_flight_passengers(Database *database, unsigned int flight_id) {
  CatalogPassenger *catalog = database_get_passenger_catalog(database);
  remove_passengers_by_flight_id(catalog, flight_id);
}

void remove_user_passengers(Database *database, char *user_id) {
  CatalogPassenger *catalog = database_get_passenger_catalog(database);
  remove_passengers_by_user_id(catalog, user_id);
}

int get_count_of_flights_belonging_to_user(Database *database, char *user_id) {
  CatalogPassenger *catalog = database_get_passenger_catalog(database);
  return count_user_flights(catalog, user_id);
}

int get_count_of_users_belonging_to_flight(Database *database,
                                           unsigned int flight_id) {
  CatalogPassenger *catalog = database_get_passenger_catalog(database);
  return count_flight_users(catalog, flight_id);
}