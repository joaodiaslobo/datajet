/**
 * @file catalog_flight.h
 * @brief Flights catalog.
 */
#ifndef CATALOG_FLIGHT_H
#define CATALOG_FLIGHT_H

#include <glib.h>

#include "data/schemas/flight.h"

typedef struct catalogFlight CatalogFlight;

/**
 * @brief Initialize a catalog of flights
 * @details Allocates memory for a new CatalogFlight structure, initializes its
 * properties, and returns a pointer to the newly created catalog.
 *
 * @return A pointer to the initialized CatalogFlight structure.
 */
CatalogFlight *initialize_flights_catalog();

/**
 * @brief Free memory allocated for a catalog of flights
 *
 * @param catalog A pointer to the CatalogFlight structure to be freed.
 */
void free_flights_catalog(CatalogFlight *catalog);

/**
 * @brief Insert a flight into the catalog
 * @details Inserts the given flight into the flight hash table of the provided
 * CatalogFlight structure, associating it with the specified key.
 *
 * @param catalog A pointer to the CatalogFlight structure.
 * @param flight A pointer to the Flight structure to be inserted.
 * @param key The key to associate with the inserted flight in the hash table.
 */
void insert_flight(CatalogFlight *catalog, Flight *flight, gpointer key);

/**
 * @brief Get the number of flights in the catalog by timestamp key
 * @details Returns the number of flights stored in the flight hash table
 * associated with the specified timestamp key.
 *
 * @param catalog A pointer to the CatalogFlight structure.
 * @param timestamp_key The timestamp key to look up.
 * @return The number of flights in the catalog associated with the specified
 * timestamp key.
 */
int catalog_get_flight_count_by_timestamp_key(CatalogFlight *catalog,
                                              int timestamp_key);

/**
 * @brief Increment the aggregate of flights by date
 * @details Increments the aggregate of flights by date in the provided
 * CatalogFlight structure, associating it with the specified key.
 *
 * @param catalog A pointer to the CatalogFlight structure.
 * @param schedule_departure_date The date to associate with the incremented
 * aggregate.
 */
void increment_flights_date_aggregate(CatalogFlight *catalog,
                                      Timestamp schedule_departure_date);

/**
 * @brief Count the number of flights in the catalog
 * @details Returns the number of flights stored in the flight hash table
 *
 * @param catalog A pointer to the CatalogFlight structure.
 * @return The number of flights in the catalog.
 */
int count_flights(CatalogFlight *catalog);

/**
 * @brief Remove a flight from the catalog by flight ID
 * @details Searches for a flight with the specified ID in the CatalogFlight
 * structure and removes it from both the flight array and hash table.
 *
 * @param catalog A pointer to the CatalogFlight structure.
 * @param flight_id The ID of the flight to be removed.
 */
void remove_flight(CatalogFlight *catalog, unsigned int flight_id);

/**
 * @brief Iterate through flights in the catalog and remove those that meet a
 * specified condition
 *
 * @param catalog A pointer to the CatalogFlight structure.
 * @param function A callback function that takes a flight and user-defined data
 * as parameters and returns TRUE if the flight should be removed, FALSE
 * otherwise.
 * @param data User-defined data to be passed to the callback function.
 */
void foreach_flight_remove(CatalogFlight *catalog, GHRFunc function,
                           void *data);

/**
 * @brief Check if a flight with a given ID exists in the catalog
 * @details Checks whether the flight hash table of the provided CatalogFlight
 * structure contains a flight with the specified ID.
 *
 * @param catalog A pointer to the CatalogFlight structure.
 * @param flight_id The ID of the flight to check for existence.
 * @return TRUE if a flight with the specified ID exists, FALSE otherwise.
 */
bool flight_exists(CatalogFlight *catalog, unsigned int flight_id);

/**
 * @brief Retrieve a flight from the catalog by flight ID
 * @details Looks up and returns the Flight structure associated with the
 * specified flight ID in the flight hash table of the provided CatalogFlight
 * structure.
 *
 * @param catalog A pointer to the CatalogFlight structure.
 * @param flight_id The ID of the flight to retrieve.
 * @return A pointer to the Flight structure if found, or NULL if not found.
 */
Flight *catalog_get_flight_by_id(CatalogFlight *catalog,
                                 unsigned int flight_id);

/**
 * @brief Sort the list of flights in the catalog by schedule departure date
 * @details Sorts the list of flights in the CatalogFlight structure by name
 * using the qsort_g_ptr_array function.
 *
 * @param catalog A pointer to the CatalogFlight structure.
 */
void catalog_sort_flights_by_schedule_departure_date(CatalogFlight *catalog);

/**
 * @brief Compare function for sorting Flight elements in an array by schedule
 * departure date
 * @details Compares two Flight elements based on their schedule departure
 * dates, allowing for sorting Flight elements in an array in descending order
 * by date and time.
 *
 * @param a A pointer to the first Flight element.
 * @param b A pointer to the second Flight element.
 * @return Negative value if the schedule departure date of 'a' is later than
 * 'b', positive value if 'a' is earlier than 'b', and zero if they are equal.
 */
int compare_flights_array_elements_by_schedule_departure_date(gpointer a,
                                                              gpointer b);

/**
 * @brief Retrieve the array of flights from the catalog
 * @details Returns a pointer to the GPtrArray containing Flight elements in the
 * provided CatalogFlight structure.
 *
 * @param catalog A pointer to the CatalogFlight structure.
 * @return A pointer to the GPtrArray containing Flight elements.
 */
GPtrArray *get_flights_array(CatalogFlight *catalog);

/**
 * @brief Finx the lower bound of a flight in the catalog by schedule departure
 *
 * @param flights A pointer to the GPtrArray containing Flight elements.
 * @return The timestamp of the lower bound of the flight in the array.
 */
int find_date_lower_bound_flights(GPtrArray *flights, Timestamp lower_limit);

#endif