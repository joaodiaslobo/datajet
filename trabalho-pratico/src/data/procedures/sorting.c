#include "data/procedures/sorting.h"

#include <glib.h>
#include <stdlib.h>

/*
 * This function is used instead of glib's implementation (g_ptr_array_sort)
 * because using standard qsort is way faster.
 */
void qsort_g_ptr_array(GPtrArray* array, GCompareFunc compare_func) {
  qsort(array->pdata, array->len, sizeof(gpointer), compare_func);
}