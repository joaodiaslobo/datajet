/**
 * @file aggregates.h
 * @brief Aggregate procedures.
 */
#ifndef AGGREGATES_H
#define AGGREGATES_H

#include <glib.h>

/**
 * @brief Increments the aggregate of an entity by date
 * @details Increments the aggregate of an entity by date in the provided
 * GHashTable structure, associating it with the specified key.
 *
 * @param entity_aggregate A pointer to the GHashTable structure.
 * @param date_key The date to associate with the incremented aggregate.
 */
void increment_entity_aggregate(GHashTable *entity_aggregate,
                                unsigned int date_key);

#endif