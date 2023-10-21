#ifndef RESERVATION_H
#define RESERVATION_H

#include <glib.h>
#include <stdint.h>

#include "data/schemas/schemas_utilities.h"

typedef struct reservation Reservation;

Reservation* create_reservation(char* id, char* user_id, char* hotel_id,
                                char* hotel_name, uint16_t city_tax,
                                char* adress, Date begin_date, Date end_date,
                                uint16_t price_per_night,
                                gboolean includes_breakfast, char* room_details,
                                uint16_t rating, char* comment);

void free_reservation(Reservation* reservation);

#endif