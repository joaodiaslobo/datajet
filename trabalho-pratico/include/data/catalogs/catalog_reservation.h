/**
 * @file catalog_reservation.h
 * @brief Reservations catalog.
 */
#ifndef CATALOG_RESERVATION_H
#define CATALOG_RESERVATION_H

#include <glib.h>

#include "data/schemas/reservation.h"

typedef struct catalogReservation CatalogReservation;

/**
 * @brief Initialize a catalog for managing reservations
 * @details Allocates memory for a new CatalogReservation structure, initializes
 * its internal data structures, and returns a pointer to the created catalog.
 *
 * @return A pointer to the newly initialized CatalogReservation structure.
 */
CatalogReservation *initialize_reservations_catalog();

/**
 * @brief Free a GPtrArray of reservation pointers and their associated memory
 * @details Frees the memory occupied by a GPtrArray of reservation pointers and
 * their associated memory.
 *
 * @param array A pointer to the GPtrArray to be freed.
 */
void free_reservation_ptr_array(void *array);

/**
 * @brief Free memory occupied by a CatalogReservation structure
 * @details Destroys the internal hash tables and frees the memory occupied by
 * the provided CatalogReservation structure.
 *
 * @param catalog A pointer to the CatalogReservation structure to be freed.
 */
void free_reservations_catalog(CatalogReservation *catalog);

/**
 * @brief Insert a reservation into the catalog
 * @details Inserts the provided reservation into the CatalogReservation
 * structure, associating it with the specified key. Additionally, associates
 * the reservation with the user ID in a separate hash table for user
 * reservations, and with the hotel ID in a separate hash table for hotel
 * reservations.
 *
 * @param catalog A pointer to the CatalogReservation structure.
 * @param reservation A pointer to the Reservation structure to be inserted.
 * @param key The key to associate with the inserted reservation in the hash
 * table.
 */
void insert_reservation(CatalogReservation *catalog, Reservation *reservation,
                        gpointer key);

/**
 * @brief Increment the aggregate of reservations by date
 * @details Increments the aggregate of reservations by date in the provided
 * CatalogReservation structure, associating it with the specified key.
 *
 * @param catalog A pointer to the CatalogReservation structure.
 * @param begin_date The date to associate with the incremented
 * aggregate.
 */
void increment_reservations_date_aggregate(CatalogReservation *catalog,
                                           Timestamp begin_date);

/**
 * @brief Get the total count of reservations in the catalog
 * @details Returns the total count of reservations stored in the
 * CatalogReservation structure.
 *
 * @param catalog A pointer to the CatalogReservation structure.
 * @return The total count of reservations in the catalog.
 */
int count_reservations(CatalogReservation *catalog);

/**
 * @brief Count the number of reservations associated with a specific user in
 * the catalog
 * @details Retrieves the list of reservations associated with the specified
 * user ID from the CatalogReservation structure and returns the number of
 * reservations in the list.
 *
 * @param catalog A pointer to the CatalogReservation structure.
 * @param user_id The ID of the user for which to count associated reservations.
 * @return The number of reservations associated with the specified user ID.
 */
int count_user_reservations(CatalogReservation *catalog, char *user_id);

/**
 * @brief Retrieve the list of reservations associated with a specific hotel in
 * the catalog
 * @details Returns a pointer to the GPtrArray containing reservation
 * information associated with the specified hotel ID in the CatalogReservation
 * structure.
 *
 * @param catalog A pointer to the CatalogReservation structure.
 * @param hotel_id The ID of the hotel for which to retrieve associated
 * reservations.
 * @return A pointer to the GPtrArray containing reservation information
 * associated with the hotel ID.
 */
GPtrArray *get_hotel_reservations(CatalogReservation *catalog,
                                  unsigned short hotel_id);

/**
 * @brief Retrieve the list of reservations associated with a specific user in
 * the catalog
 * @details Returns a pointer to the GPtrArray containing reservation
 * information associated with the specified user ID in the CatalogReservation
 * structure.
 *
 * @param catalog A pointer to the CatalogReservation structure.
 * @param user_id The ID of the user for which to retrieve associated
 * reservations.
 * @return A pointer to the GPtrArray containing reservation information
 * associated with the user ID.
 */
GPtrArray *get_user_reservations(CatalogReservation *catalog, char *user_id);

/**
 * @brief Get a user's reservation by index from the catalog
 * @details Retrieves a specific reservation associated with the specified user
 * ID from the CatalogReservation structure based on the provided index.
 *
 * @param catalog A pointer to the CatalogReservation structure.
 * @param user_id The ID of the user for which to retrieve associated
 * reservations.
 * @param index The index of the reservation to retrieve from the user's
 * reservation list.
 * @return A pointer to the Reservation structure associated with the user and
 * index, or NULL if the user ID is not found or the index is out of bounds.
 */
Reservation *get_user_reservation_by_index(CatalogReservation *catalog,
                                           char *user_id, int index);

/**
 * @brief Retrieve a reservation by ID from the catalog
 * @details Returns a pointer to the Reservation structure associated with the
 * specified reservation ID in the CatalogReservation structure.
 *
 * @param catalog A pointer to the CatalogReservation structure.
 * @param reservation_id The ID of the reservation to retrieve.
 * @return A pointer to the Reservation structure associated with the
 * reservation ID, or NULL if the reservation ID is not found.
 */
Reservation *catalog_get_reservation_by_id(CatalogReservation *catalog,
                                           unsigned int reservation_id);

/**
 * @brief Get the number of reservations in the catalog by timestamp key
 * @details Returns the number of reservations stored in the reservation hash
 * table associated with the specified timestamp key.
 *
 * @param catalog A pointer to the CatalogReservation structure.
 * @param timestamp_key The timestamp key to look up.
 * @return The number of reservations in the catalog associated with the
 * specified timestamp key.
 */
int catalog_get_reservation_count_by_timestamp_key(CatalogReservation *catalog,
                                                   int timestamp_key);

/**
 * @brief Compare two reservation elements based on their begin dates
 * @details Compares two reservation elements based on their begin dates.
 * Returns -1 if the begin date of the first reservation is greater, 1 if the
 * begin date of the second reservation is greater, and 0 if both begin dates
 * are equal.
 *
 * @param a A pointer to the first Reservation element.
 * @param b A pointer to the second Reservation element.
 * @return -1 if the begin date of the first reservation is greater,
 *          1 if the begin date of the second reservation is greater,
 *          0 if both begin dates are equal.
 */
int compare_reservations_array_elements_by_begin_date(gpointer a, gpointer b);

#endif