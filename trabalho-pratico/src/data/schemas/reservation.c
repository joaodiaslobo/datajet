#include "data/schemas/reservation.h"

#include <glib.h>
#include <stdint.h>

#include "data/schemas/schemas_utilities.h"

struct reservation {
  char* id;
  char* user_id;
  char* hotel_id;
  char* hotel_name;
  uint16_t city_tax;
  char* address;
  Date begin_date;
  Date end_date;
  uint16_t price_per_night;
  gboolean includes_breakfast;
  char* room_details;
  uint16_t rating;
  char* comment;
};

Reservation* create_reservation(char* id, char* user_id, char* hotel_id,
                                char* hotel_name, uint16_t city_tax,
                                char* address, Date begin_date, Date end_date,
                                uint16_t price_per_night,
                                gboolean includes_breakfast, char* room_details,
                                uint16_t rating, char* comment) {
  Reservation* reservation = malloc(sizeof(struct reservation));

  reservation->id = g_strdup(id);
  reservation->user_id = g_strdup(user_id);
  reservation->hotel_id = g_strdup(hotel_id);
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

void free_reservation(Reservation* reservation) {
  g_free(reservation->id);
  g_free(reservation->user_id);
  g_free(reservation->hotel_id);
  g_free(reservation->hotel_name);
  g_free(reservation->address);
  g_free(reservation->room_details);
  g_free(reservation->comment);
  free(reservation);
}