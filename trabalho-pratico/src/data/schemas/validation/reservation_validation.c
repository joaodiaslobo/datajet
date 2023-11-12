#include "data/schemas/validation/reservation_validation.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "data/schemas/validation/generic_validation.h"

bool invalid_hotel_stars(char* hotel_stars) {
  return !(strlen(hotel_stars) == 1 && hotel_stars[0] >= 49 &&
           hotel_stars[0] <= 53);
}

bool invalid_city_tax(char* city_tax) {
  return (city_tax[0] != 48 && invalid_positive_integer(city_tax));
}

bool invalid_rating(char* rating) {
  return !(strlen(rating) == 0 ||
           (strlen(rating) == 1 && rating[0] >= 49 && rating[0] <= 53));
}