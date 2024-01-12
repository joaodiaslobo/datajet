/**
 * @file catalog_passenger.h
 * @brief Passengers catalog.
 */
#ifndef CATALOG_PASSENGER_H
#define CATALOG_PASSENGER_H

#include <glib.h>

#include "data/schemas/passenger.h"
#include "data/schemas/schema_data_types.h"

typedef struct catalogPassenger CatalogPassenger;

/**
 * @brief Initialize a catalog for managing passenger information
 * @details Allocates memory for a new CatalogPassenger structure, initializes
 * its internal data structures, and returns a pointer to the created catalog.
 *
 * @return A pointer to the newly initialized CatalogPassenger structure.
 */
CatalogPassenger *initialize_passengers_catalog();

/**
 * @brief Free a GPtrArray and its elements
 * @details Frees the memory occupied by a GPtrArray and its elements.
 *
 * @param array A pointer to the GPtrArray to be freed.
 */
void free_ptr_array(void *array);

/**
 * @brief Free a GHashTable and its elements
 * @details Frees the memory occupied by a GHashTable and its elements.
 *
 * @param hash_table A pointer to the GHashTable to be freed.
 */
void free_hash_table(void *hash_table);

/**
 * @brief Free memory occupied by a CatalogPassenger structure
 * @details Destroys the internal hash tables and frees the memory occupied by
 * the provided CatalogPassenger structure.
 *
 * @param catalog A pointer to the CatalogPassenger structure to be freed.
 */
void free_passengers_catalog(CatalogPassenger *catalog);

/**
 * @brief Insert passenger information into the catalog
 * @details Inserts the provided user and flight information into the
 * CatalogPassenger structure, associating them with the specified flight ID and
 * user ID. If the flight ID or user ID does not exist in the catalog, new
 * entries are created.
 *
 * @param catalog A pointer to the CatalogPassenger structure.
 * @param flight_id The ID of the flight to associate the passenger with.
 * @param user_id_unsafe The unsafe pointer to the user ID string.
 * @param flight A pointer to the flight information to be associated with the
 * passenger.
 * @param user A pointer to the user information to be associated with the
 * passenger.
 */
void insert_passenger(CatalogPassenger *catalog, unsigned int flight_id,
                      char *user_id_unsafe, void *flight, void *user);

/**
 * @brief Increment the aggregate of passengers by date
 * @details Increments the aggregate of passengers by date in the provided
 * CatalogPassenger structure, associating it with the specified key.
 *
 * @param catalog A pointer to the CatalogPassenger structure.
 * @param schedule_departure_date The date to associate with the incremented
 * aggregate.
 */
void increment_passengers_date_aggregate(CatalogPassenger *catalog,
                                         Timestamp schedule_departure_date);

/**
 * @brief Increment the aggregate of unique passengers by date
 * @details Increments the aggregate of unique passengers by date in the
 * provided CatalogPassenger structure, associating it with the specified key.
 *
 * @param catalog A pointer to the CatalogPassenger structure.
 * @param schedule_departure_date The date to associate with the incremented
 * aggregate
 * @param user_id The user id to associate with the current incremented
 * aggregate.
 */
void increment_unique_passengers_date_aggregate(
    CatalogPassenger *catalog, Timestamp schedule_departure_date,
    char *user_id);

/**
 * @brief Increments the aggregate of an entity by date
 * @details Increments the aggregate of an entity by date in the provided
 * GHashTable structure, associating it with the specified key and recording its
 * uniqueness.
 *
 * @param hash_table A pointer to the GHashTable structure.
 * @param timestamp_key The date to associate with the incremented aggregate.
 * @param user_id The user id to associate with the current incremented
 * aggregate.
 */
void increment_hash_aggregate(GHashTable *hash_table,
                              unsigned int timestamp_key, char *user_id);

/**
 * @brief Count the number of users associated with a specific flight in the
 * catalog
 * @details Retrieves the list of users associated with the specified flight ID
 * from the CatalogPassenger structure and returns the number of users in the
 * list.
 *
 * @param catalog A pointer to the CatalogPassenger structure.
 * @param flight_id The ID of the flight for which to count associated users.
 * @return The number of users associated with the specified flight ID.
 */
int count_flight_users(CatalogPassenger *catalog, unsigned int flight_id);

/**
 * @brief Count the number of flights associated with a specific user in the
 * catalog
 * @details Retrieves the list of flights associated with the specified user ID
 * from the CatalogPassenger structure and returns the number of flights in the
 * list.
 *
 * @param catalog A pointer to the CatalogPassenger structure.
 * @param user_id The ID of the user for which to count associated flights.
 * @return The number of flights associated with the specified user ID.
 */
int count_user_flights(CatalogPassenger *catalog, char *user_id);

/**
 * @brief Remove all passenger information associated with a user ID from the
 * catalog
 * @details Removes all passenger information associated with the specified user
 * ID from the CatalogPassenger structure, including user information from
 * flight user lists and flight information from the user flight list.
 *
 * @param catalog A pointer to the CatalogPassenger structure.
 * @param user_id The user ID for which passenger information is to be removed.
 */
void remove_passengers_by_user_id(CatalogPassenger *catalog, char *user_id);

/**
 * @brief Remove all passenger information associated with a flight ID from the
 * catalog
 * @details Removes all passenger information associated with the specified
 * flight ID from the CatalogPassenger structure, including user information
 * from flight user lists and flight information from user flight lists.
 *
 * @param catalog A pointer to the CatalogPassenger structure.
 * @param flight_id The ID of the flight for which passenger information is to
 * be removed.
 */
void remove_passengers_by_flight_id(CatalogPassenger *catalog,
                                    unsigned int flight_id);

/**
 * @brief Get the total count of passengers in the catalog
 * @details Returns the total count of passengers stored in the CatalogPassenger
 * structure.
 *
 * @param catalog A pointer to the CatalogPassenger structure.
 * @return The total count of passengers in the catalog.
 */
int count_passengers(CatalogPassenger *catalog);

int catalog_get_passenger_count_by_timestamp_key(CatalogPassenger *catalog,
                                                 int timestamp_key);

int catalog_get_unique_passenger_count_by_timestamp_key(
    CatalogPassenger *catalog, int timestamp_key);

/**
 * @brief Retrieve the list of flights associated with a specific user in the
 * catalog
 * @details Returns a pointer to the GPtrArray containing flight information
 * associated with the specified user ID in the CatalogPassenger structure.
 *
 * @param catalog A pointer to the CatalogPassenger structure.
 * @param user_id The ID of the user for which to retrieve associated flights.
 * @return A pointer to the GPtrArray containing flight information associated
 * with the user ID.
 */
GPtrArray *get_user_flights(CatalogPassenger *catalog, char *user_id);

#endif