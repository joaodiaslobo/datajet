/**
 * @file database.h
 * @brief Database operations.
 */
#ifndef DATABASE_H
#define DATABASE_H

#include "catalogs/catalog_airport.h"
#include "catalogs/catalog_flight.h"
#include "catalogs/catalog_passenger.h"
#include "catalogs/catalog_reservation.h"
#include "catalogs/catalog_user.h"

#define OUTPUT_DIRECTORY "Resultados"

typedef struct database Database;

/**
 * @brief Initializes the database.
 * @details Initializes the database.
 *
 * @return Initialized database.
 */
Database *initialize_database();

/**
 * @brief Frees the database.
 * @details Frees the data used by the database.
 *
 * @param database Database.
 */
void free_database(Database *database);

/**
 * @brief Populates the database with the given dataset.
 * @details Populates the database with the given dataset composed of multiple
 * csv files.
 *
 * @param database Database.
 * @param csv_dataset_path Path to the CSV dataset.
 * @return 0 if the execution succeeded.
 */
int csv_populate_database(Database *database, char *csv_dataset_path);

/**
 * @brief Gets the user catalog.
 * @details Gets the user catalog.
 *
 * @param database Database.
 * @return User catalog.
 */
CatalogUser *database_get_user_catalog(Database *database);

/**
 * @brief Gets the flight catalog.
 * @details Gets the flight catalog.
 *
 * @param database Database.
 * @return Flight catalog.
 */
CatalogFlight *database_get_flight_catalog(Database *database);

/**
 * @brief Gets the passenger catalog.
 * @details Gets the passenger catalog.
 *
 * @param database Database.
 * @return Passenger catalog.
 */
CatalogPassenger *database_get_passenger_catalog(Database *database);

/**
 * @brief Gets the reservation catalog.
 * @details Gets the reservation catalog.
 *
 * @param database Database.
 * @return Reservation catalog.
 */
CatalogReservation *database_get_reservation_catalog(Database *database);

/**
 * @brief Gets the airport catalog.
 * @details Gets the airport catalog.
 *
 * @param database Database.
 * @return Airport catalog.
 */
CatalogAirport *database_get_airport_catalog(Database *database);

#endif