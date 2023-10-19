#include "data/database.h"

struct Database {
  CatalogUser *userCatalog;
  CatalogFlight *flightCatalog;
  CatalogPassenger *passengerCatalog;
  CatalogReservation *reservationCatalog;
};