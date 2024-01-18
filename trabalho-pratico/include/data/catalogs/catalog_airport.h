/**
 * @file catalog_airport.h
 * @brief Airports catalog.
 */
#ifndef CATALOG_AIRPORT_H
#define CATALOG_AIRPORT_H

#include <glib.h>

typedef struct catalogAirport CatalogAirport;

typedef struct airportData AirportData;

typedef struct airportDelayMedian AirportDelayMedian;

/**
 * @brief Initialize a catalog of airports
 * @details Allocates memory for a new CatalogAirport structure, initializes its
 * properties, and returns a pointer to the newly created catalog.
 *
 * @return A pointer to the initialized CatalogAirport structure.
 */
CatalogAirport *initialize_airports_catalog();

/**
 * @brief Free memory allocated for airport data
 *
 * @param data A pointer to the AirportData structure to be freed.
 */
void free_airport_data(AirportData *data);

/**
 * @brief Free memory allocated for airport delay median
 *
 * @param airport A pointer to the AirportDelayMedian structure to be freed.
 */
void free_airport_median(AirportDelayMedian *airport);

/**
 * @brief Insert a flight delay that departured from a certain airport into the
 * catalog
 * @details Inserts the given delay into the airport hash table of the provided
 * CatalogAirport structure, associating it with the specified key (airport id).
 *
 * @param catalog A pointer to the CatalogAirport structure.
 * @param airport_id The airport id to associate with the inserted delay in the
 * hash table.
 * @param delay The delay value to be inserted.
 */
void insert_airport_delay(CatalogAirport *catalog, char *airport_id, int delay);

/**
 * @brief Insert an airport into the catalog
 * @details Inserts the given airport into the airport hash table of the
 * provided CatalogAirport structure, associating it with the specified key
 * (airport id).
 *
 * @param catalog A pointer to the CatalogAirport structure.
 * @param airport_id The airport id to associate with the inserted airport in
 * the hash table.
 */
void insert_airport(CatalogAirport *catalog, char *airport_id);

/**
 * @brief Organize the data in a catalog of airports
 * @details Builds necessary optimized data structures required by airport
 * queries
 *
 * @param catalog A pointer to the CatalogAirport structure.
 */
void catalog_airport_organize_data(CatalogAirport *catalog);

/**
 * @brief Free memory allocated for a catalog of airports
 *
 * @param catalog A pointer to the CatalogAirport structure to be freed.
 */
void free_airports_catalog(CatalogAirport *catalog);

/**
 * @brief Compare delays.
 * @details Compares two delay values for sorting delays in an array in
 * ascending order.
 *
 * @param a A pointer to the first delay.
 * @param b A pointer to the second delay.
 * @return Negative value if the delay 'a' is smaller than
 * 'b', positive value if 'a' is bigger than 'b', and zero if they are equal.
 */
int compare_delays(gpointer a, gpointer b);

/**
 * @brief Compare medians.
 * @details Compares two median values for sorting medians in an array in
 * ascending order.
 *
 * @param a A pointer to the first median.
 * @param b A pointer to the second median.
 * @return Negative value if the median 'a' is smaller than
 * 'b', positive value if 'a' is bigger than 'b', and zero if they are equal.
 */
int compare_medians(gpointer a, gpointer b);

/**
 * @brief Retrieves an airport id from the airport delay median
 * @details Looks up and returns the airport id in the provided
 * AirportDelayMedian structure.
 *
 * @param airport A pointer to the AirportDelayMedian structure.
 * @return A pointer to the airport id if found, or NULL if not found.
 */
char *airport_delay_median_get_airport_id(AirportDelayMedian *airport);

/**
 * @brief Retrieves an delay median from the airport delay median
 * @details Looks up and returns the delay median in the provided
 * AirportDelayMedian structure.
 *
 * @param airport A pointer to the AirportDelayMedian structure.
 * @return The delay median.
 */
int airport_delay_median_get_delay_median(AirportDelayMedian *airport);

/**
 * @brief Gets airport delays
 * @details Looks up and returns an array with airport delays in the provided
 * CatalogAirport structure.
 *
 * @param airport A pointer to the CatalogAirport structure.
 * @return A pointer to the array.
 */
GPtrArray *catalog_get_airport_delays(CatalogAirport *catalog);

#endif