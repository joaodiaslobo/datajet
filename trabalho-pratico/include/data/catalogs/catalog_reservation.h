#ifndef CATALOG_RESERVATION_H
#define CATALOG_RESERVATION_H

#include <glib.h>

#include "data/schemas/reservation.h"

typedef struct catalogReservation CatalogReservation;

CatalogReservation *initialize_reservations_catalog();

void free_reservations_catalog(CatalogReservation *catalog);

void insert_reservation(CatalogReservation *catalog, Reservation *reservation);

int count_reservations(CatalogReservation *catalog);

Reservation *catalog_get_reservation_by_id(CatalogReservation *catalog,
                                           int reservation_id);

#endif