#include <glib.h>

void increment_entity_aggregate(GHashTable *entity_aggregate,
                                unsigned int date_key) {
  unsigned int *date_aggregate =
      g_hash_table_lookup(entity_aggregate, GUINT_TO_POINTER(date_key));
  if (date_aggregate == NULL) {
    date_aggregate = malloc(sizeof(unsigned int));
    *date_aggregate = 0;
    g_hash_table_insert(entity_aggregate, GUINT_TO_POINTER(date_key),
                        date_aggregate);
  }
  (*date_aggregate)++;
}