#ifndef RESERVATION_H
#define RESERVATION_H

#include <glib.h>
#include <stdbool.h>

#include "data/schemas/schema_data_types.h"
#include "io/parsing/reader.h"

typedef struct reservation Reservation;

Reservation* create_reservation(unsigned short id, char* user_id,
                                char* hotel_id, char* hotel_name,
                                int hotel_stars, int city_tax, char* address,
                                Timestamp begin_date, Timestamp end_date,
                                int price_per_night, bool includes_breakfast,
                                char* room_details, int rating, char* comment);

void free_reservation(void* reservation_ptr);

int parse_reservation_and_add_to_catalog(RowReader* reader, void* catalog,
                                         void* database);

bool reservation_invalid_association(void* database, char* user_id);

unsigned short reservation_get_id(Reservation* reservation);

char* reservation_get_user_id(Reservation* reservation);

char* reservation_get_hotel_id(Reservation* reservation);

char* reservation_get_hotel_name(Reservation* reservation);

int reservation_get_hotel_stars(Reservation* reservation);

int reservation_get_city_tax(Reservation* reservation);

char* reservation_get_address(Reservation* reservation);

Timestamp reservation_get_begin_date(Reservation* reservation);

Timestamp reservation_get_end_date(Reservation* reservation);

int reservation_get_price_per_night(Reservation* reservation);

bool reservation_get_includes_breakfast(Reservation* reservation);

char* reservation_get_room_details(Reservation* reservation);

int reservation_get_rating(Reservation* reservation);

char* reservation_get_comment(Reservation* reservation);

int reservation_get_number_of_nights(Reservation* reservation);

double reservation_get_total_price(Reservation* reservation);

#endif