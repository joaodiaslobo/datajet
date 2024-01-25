/**
 * @file filtering.h
 * @brief Filtering procedures.
 */
#ifndef FILTERING_H
#define FILTERING_H
#include <glib.h>

#include "data/schemas/schema_data_types.h"

typedef Timestamp(timestamp_func)(void *);

/**
 * @brief Finds the lower bound of a date in a GPtrArray.
 * @details Finds the lower bound of a date in a GPtrArray using the given
 * timestamp function.
 *
 * @param array The GPtrArray to search.
 * @param lower_limit The lower limit to search for.
 * @param func The timestamp function to use.
 * @return The lower bound of the date in the GPtrArray.
 */
int find_date_lower_bound(GPtrArray *array, Timestamp lower_limit,
                          timestamp_func func);

#endif