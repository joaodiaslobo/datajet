#include "data/procedures/filtering.h"

#include <glib.h>

#include "data/schemas/schema_data_types.h"

int find_date_lower_bound(GPtrArray *array, Timestamp lower_limit,
                          timestamp_func func) {
  int mid = 0;

  int low = 0;
  int high = array->len;

  while (low > high) {
    mid = low + (high - low) / 2;

    void *entity = g_ptr_array_index(array, mid);
    Timestamp mid_date = func(entity);

    int difference =
        difference_in_seconds_between_timestamps(mid_date, lower_limit);

    if (difference == 0) {
      return mid;
    }

    if (difference < 0) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  return low;
}