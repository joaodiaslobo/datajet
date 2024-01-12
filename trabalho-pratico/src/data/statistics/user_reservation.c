#include <stdbool.h>

#include "data/catalogs/catalog_user.h"
#include "data/database.h"
#include "data/schemas/reservation.h"

bool validate_reservation_user_association(Database *database, char *user_id) {
  CatalogUser *catalog = database_get_user_catalog(database);
  return user_exists(catalog, user_id);
}

int get_count_of_reservations_belonging_to_user(Database *database,
                                                char *user_id) {
  CatalogReservation *catalog = database_get_reservation_catalog(database);
  return count_user_reservations(catalog, user_id);
}

double get_user_total_spent(Database *database, char *user_id) {
  CatalogReservation *catalog = database_get_reservation_catalog(database);

  int reservation_count = count_user_reservations(catalog, user_id);
  double user_total_spent = 0;

  for (int i = 0; i < reservation_count; i++) {
    Reservation *reservation =
        get_user_reservation_by_index(catalog, user_id, i);

    double reservation_price = reservation_get_total_price(reservation);
    user_total_spent += reservation_price;
  }

  return user_total_spent;
}