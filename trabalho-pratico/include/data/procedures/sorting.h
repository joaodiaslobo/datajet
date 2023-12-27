/**
 * @file sorting.h
 * @brief Sorting procedures.
 */
#ifndef SORTING_H
#define SORTING_H

#include <glib.h>

/**
 * @brief Sorts a GPtrArray using the given compare function.
 *
 * @param array The GPtrArray to sort.
 * @param compare_func The compare function to use.
 */
void qsort_g_ptr_array(GPtrArray* array, GCompareFunc compare_func);

#endif