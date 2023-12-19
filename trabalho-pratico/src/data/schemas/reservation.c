#include "data/schemas/reservation.h"

#include <glib.h>
#include <stdbool.h>
#include <stdint.h>

#include "data/catalogs/catalog_reservation.h"
#include "data/schemas/schema_data_types.h"
#include "data/schemas/validation/generic_validation.h"
#include "data/schemas/validation/reservation_validation.h"
#include "data/statistics/user_reservation.h"
#include "io/parsing/reader.h"

struct reservation {
  unsigned int id;
  char* user_id;
  char* hotel_id;
  char* hotel_name;
  int hotel_stars;
  int city_tax;
  char* address;
  Timestamp begin_date;
  Timestamp end_date;
  int price_per_night;
  bool includes_breakfast;
  char* room_details;
  int rating;
  char* comment;
};

Reservation* create_reservation(unsigned int id, char* user_id, char* hotel_id,
                                char* hotel_name, int hotel_stars, int city_tax,
                                char* address, Timestamp begin_date,
                                Timestamp end_date, int price_per_night,
                                bool includes_breakfast, char* room_details,
                                int rating, char* comment) {
  Reservation* reservation = malloc(sizeof(struct reservation));

  reservation_set_id(reservation, id);
  reservation_set_user_id(reservation, user_id);
  reservation_set_hotel_id(reservation, hotel_id);
  reservation_set_hotel_stars(reservation, hotel_stars);
  reservation_set_hotel_name(reservation, hotel_name);
  reservation_set_city_tax(reservation, city_tax);
  reservation_set_address(reservation, address);
  reservation_set_begin_date(reservation, begin_date);
  reservation_set_end_date(reservation, end_date);
  reservation_set_price_per_night(reservation, price_per_night);
  reservation_set_includes_breakfast(reservation, includes_breakfast);
  reservation_set_room_details(reservation, room_details);
  reservation_set_rating(reservation, rating);
  reservation_set_comment(reservation, comment);

  return reservation;
}

int parse_reservation_and_add_to_catalog(RowReader* reader, void* catalog,
                                         void* database) {
  char* reservation_id_string = reader_next_cell(reader);
  if (is_empty_value(reservation_id_string)) return 1;

  unsigned int reservation_id =
      parse_unsigned_integer(reservation_id_string + 4);
  gpointer reservation_key = GUINT_TO_POINTER(reservation_id);

  char* reservation_user_id = reader_next_cell(reader);
  if (is_empty_value(reservation_user_id)) return 1;

  if (reservation_invalid_association(database, reservation_user_id)) return 1;

  char* reservation_hotel_id = reader_next_cell(reader);
  if (is_empty_value(reservation_hotel_id)) return 1;

  char* reservation_hotel_name = reader_next_cell(reader);
  if (is_empty_value(reservation_hotel_name)) return 1;

  char* reservation_hotel_stars_string = reader_next_cell(reader);
  if (invalid_hotel_stars(reservation_hotel_stars_string)) return 1;
  int reservation_hotel_stars = parse_number(reservation_hotel_stars_string);

  char* reservation_city_tax_string = reader_next_cell(reader);
  if (invalid_city_tax(reservation_city_tax_string)) return 1;
  int reservation_city_tax = parse_number(reservation_city_tax_string);

  char* reservation_address = reader_next_cell(reader);
  if (is_empty_value(reservation_address)) return 1;

  char* reservation_begin_date_string = reader_next_cell(reader);
  if (invalid_date(reservation_begin_date_string)) return 1;
  Timestamp reservation_begin_date = parse_date(reservation_begin_date_string);

  char* reservation_end_date_string = reader_next_cell(reader);
  if (invalid_date(reservation_end_date_string)) return 1;
  Timestamp reservation_end_date = parse_date(reservation_end_date_string);

  if (reservation_begin_date.date > reservation_end_date.date) return 1;

  char* reservation_price_per_night_string = reader_next_cell(reader);
  if (invalid_positive_integer(reservation_price_per_night_string)) return 1;
  int reservation_price_per_night =
      parse_number(reservation_price_per_night_string);

  char* reservation_includes_breakfast_string = reader_next_cell(reader);
  if (invalid_bool_value(reservation_includes_breakfast_string)) return 1;
  bool reservation_includes_breakfast =
      parse_boolean(reservation_includes_breakfast_string);

  char* reservation_room_details = reader_next_cell(reader);

  char* reservation_rating_string = reader_next_cell(reader);
  if (invalid_rating(reservation_rating_string)) return 1;
  int reservation_rating = parse_number(reservation_rating_string);

  char* reservation_comment = reader_next_cell(reader);

  Reservation* reservation = create_reservation(
      reservation_id, reservation_user_id, reservation_hotel_id,
      reservation_hotel_name, reservation_hotel_stars, reservation_city_tax,
      reservation_address, reservation_begin_date, reservation_end_date,
      reservation_price_per_night, reservation_includes_breakfast,
      reservation_room_details, reservation_rating, reservation_comment);

  insert_reservation(catalog, reservation, reservation_key);

  return 0;
}

bool reservation_invalid_association(void* database, char* user_id) {
  return !validate_reservation_user_association(database, user_id);
}

void free_reservation(void* reservation_ptr) {
  Reservation* reservation = (Reservation*)reservation_ptr;
  g_free(reservation->user_id);
  g_free(reservation->hotel_id);
  g_free(reservation->hotel_name);
  g_free(reservation->address);
  g_free(reservation->room_details);
  g_free(reservation->comment);
  free(reservation);
}

unsigned int reservation_get_id(Reservation* reservation) {
  return reservation->id;
}

void reservation_set_id(Reservation* reservation, unsigned int id) {
  reservation->id = id;
}

char* reservation_get_user_id(Reservation* reservation) {
  return g_strdup(reservation->user_id);
}

void reservation_set_user_id(Reservation* reservation, char* user_id) {
  reservation->user_id = g_strdup(user_id);
}

char* reservation_get_hotel_id(Reservation* reservation) {
  return g_strdup(reservation->hotel_id);
}

void reservation_set_hotel_id(Reservation* reservation, char* hotel_id) {
  reservation->hotel_id = g_strdup(hotel_id);
}

char* reservation_get_hotel_name(Reservation* reservation) {
  return g_strdup(reservation->hotel_name);
}

void reservation_set_hotel_name(Reservation* reservation, char* hotel_name) {
  reservation->hotel_name = g_strdup(hotel_name);
}

int reservation_get_hotel_stars(Reservation* reservation) {
  return reservation->hotel_stars;
}

void reservation_set_hotel_stars(Reservation* reservation, int hotel_stars) {
  reservation->hotel_stars = hotel_stars;
}

int reservation_get_city_tax(Reservation* reservation) {
  return reservation->city_tax;
}

void reservation_set_city_tax(Reservation* reservation, int city_tax) {
  reservation->city_tax = city_tax;
}

char* reservation_get_address(Reservation* reservation) {
  return g_strdup(reservation->address);
}

void reservation_set_address(Reservation* reservation, char* address) {
  reservation->address = g_strdup(address);
}

Timestamp reservation_get_begin_date(Reservation* reservation) {
  return reservation->begin_date;
}

void reservation_set_begin_date(Reservation* reservation,
                                Timestamp begin_date) {
  reservation->begin_date = begin_date;
}

Timestamp reservation_get_end_date(Reservation* reservation) {
  return reservation->end_date;
}

void reservation_set_end_date(Reservation* reservation, Timestamp end_date) {
  reservation->end_date = end_date;
}

int reservation_get_price_per_night(Reservation* reservation) {
  return reservation->price_per_night;
}

void reservation_set_price_per_night(Reservation* reservation,
                                     int price_per_night) {
  reservation->price_per_night = price_per_night;
}

bool reservation_get_includes_breakfast(Reservation* reservation) {
  return reservation->includes_breakfast;
}

void reservation_set_includes_breakfast(Reservation* reservation,
                                        bool includes_breakfast) {
  reservation->includes_breakfast = includes_breakfast;
}

char* reservation_get_room_details(Reservation* reservation) {
  return g_strdup(reservation->room_details);
}

void reservation_set_room_details(Reservation* reservation,
                                  char* room_details) {
  reservation->room_details = g_strdup(room_details);
}

int reservation_get_rating(Reservation* reservation) {
  return reservation->rating;
}

void reservation_set_rating(Reservation* reservation, int rating) {
  reservation->rating = rating;
}

char* reservation_get_comment(Reservation* reservation) {
  return g_strdup(reservation->comment);
}

void reservation_set_comment(Reservation* reservation, char* comment) {
  reservation->comment = g_strdup(comment);
}

int reservation_get_number_of_nights(Reservation* reservation) {
  return timestamp_get_difference_in_days(reservation->begin_date,
                                          reservation->end_date);
}

double reservation_get_total_price(Reservation* reservation) {
  int reservation_number_of_nights =
      reservation_get_number_of_nights(reservation);
  int reservation_price_per_night =
      reservation_get_price_per_night(reservation);
  int reservation_city_tax = reservation_get_city_tax(reservation);

  double reservation_gross_price =
      reservation_price_per_night * reservation_number_of_nights;

  return reservation_gross_price +
         (reservation_gross_price / 100) * reservation_city_tax;
}