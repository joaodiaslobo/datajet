#include <stdbool.h>

#include "data/catalogs/catalog_user.h"
#include "data/database.h"

int validate_reservation_user_association(Database *database, char *user_id) {
  // Checks if the user exists
  CatalogUser *catalog = database_get_user_catalog(database);
  return user_exists(catalog, user_id);
}