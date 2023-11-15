#ifndef CATALOG_RESERVATION_H
#define CATALOG_RESERVATION_H

#include <glib.h>

#include "data/schemas/reservation.h"

typedef struct catalogReservation CatalogReservation;

CatalogReservation *initialize_reservations_catalog();

void free_reservation_ptr_array(void *array);

void free_reservations_catalog(CatalogReservation *catalog);

void insert_reservation(CatalogReservation *catalog, Reservation *reservation,
                        gpointer key);

int count_reservations(CatalogReservation *catalog);

int count_user_reservations(CatalogReservation *catalog, char *user_id);

GPtrArray *get_hotel_reservations(CatalogReservation *catalog, char *hotel_id);

Reservation *get_user_reservation_by_index(CatalogReservation *catalog,
                                           char *user_id, int index);

Reservation *catalog_get_reservation_by_id(CatalogReservation *catalog,
                                           int reservation_id);

int compare_reservations_array_elements_by_begin_date(gpointer a, gpointer b);

#endif