#ifndef RESERVATIONS_VALIDATION_H
#define RESERVATIONS_VALIDATION_H

#include "data/schemas/schema_data_types.h"

bool invalid_hotel_stars(char* hotel_stars);

bool invalid_city_tax(char* city_tax);

bool invalid_rating(char* rating);

#endif