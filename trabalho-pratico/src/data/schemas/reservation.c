#include "data/schemas/reservation.h"

#include <glib.h>
#include <stdbool.h>
#include <stdint.h>

#include "data/catalogs/catalog_reservation.h"
#include "data/schemas/schema_data_types.h"
#include "io/parsing/reader.h"

struct reservation {
  char* id;
  char* user_id;
  char* hotel_id;
  char* hotel_name;
  int hotel_stars;
  int city_tax;
  char* address;
  Timestamp* begin_date;
  Timestamp* end_date;
  int price_per_night;
  bool includes_breakfast;
  char* room_details;
  int rating;
  char* comment;
};

Reservation* create_reservation(char* id, char* user_id, char* hotel_id,
                                char* hotel_name, int hotel_stars, int city_tax,
                                char* address, Timestamp* begin_date,
                                Timestamp* end_date, int price_per_night,
                                bool includes_breakfast, char* room_details,
                                int rating, char* comment) {
  Reservation* reservation = malloc(sizeof(struct reservation));

  reservation->id = g_strdup(id);
  reservation->user_id = g_strdup(user_id);
  reservation->hotel_id = g_strdup(hotel_id);
  reservation->hotel_stars = hotel_stars;
  reservation->hotel_name = g_strdup(hotel_name);
  reservation->city_tax = city_tax;
  reservation->address = g_strdup(address);
  reservation->begin_date = begin_date;
  reservation->end_date = end_date;
  reservation->price_per_night = price_per_night;
  reservation->includes_breakfast = includes_breakfast;
  reservation->room_details = g_strdup(room_details);
  reservation->rating = rating;
  reservation->comment = g_strdup(comment);

  return reservation;
}

int parse_reservation_and_add_to_catalog(RowReader* reader, void* catalog) {
  char* reservation_id = reader_next_cell(reader);
  char* reservation_user_id = reader_next_cell(reader);
  char* reservation_hotel_id = reader_next_cell(reader);
  char* reservation_hotel_name = reader_next_cell(reader);
  int reservation_hotel_stars = parse_number(reader_next_cell(reader));
  int reservation_city_tax = parse_number(reader_next_cell(reader));
  char* reservation_address = reader_next_cell(reader);
  Timestamp* reservation_begin_date = parse_date(reader_next_cell(reader));
  Timestamp* reservation_end_date = parse_date(reader_next_cell(reader));
  int reservation_price_per_night = parse_number(reader_next_cell(reader));
  bool reservation_includes_breakfast = parse_boolean(reader_next_cell(reader));
  char* reservation_room_details = reader_next_cell(reader);
  int reservation_rating = parse_number(reader_next_cell(reader));
  char* reservation_comment = reader_next_cell(reader);

  Reservation* reservation = create_reservation(
      reservation_id, reservation_user_id, reservation_hotel_id,
      reservation_hotel_name, reservation_hotel_stars, reservation_city_tax,
      reservation_address, reservation_begin_date, reservation_end_date,
      reservation_price_per_night, reservation_includes_breakfast,
      reservation_room_details, reservation_rating, reservation_comment);

  insert_reservation(catalog, reservation);

  return 0;
}

void free_reservation(void* reservation_ptr) {
  Reservation* reservation = (Reservation*)reservation_ptr;
  g_free(reservation->id);
  g_free(reservation->user_id);
  g_free(reservation->hotel_id);
  g_free(reservation->hotel_name);
  g_free(reservation->address);
  free(reservation->begin_date);
  free(reservation->end_date);
  g_free(reservation->room_details);
  g_free(reservation->comment);
  free(reservation);
}

char* reservation_get_id(Reservation* reservation) {
  return g_strdup(reservation->id);
}

char* reservation_get_hotel_name(Reservation* reservation) {
  return g_strdup(reservation->hotel_name);
}

int reservation_get_hotel_stars(Reservation* reservation) {
  return reservation->hotel_stars;
}

int reservation_get_price_per_night(Reservation* reservation) {
  return reservation->price_per_night;
}
