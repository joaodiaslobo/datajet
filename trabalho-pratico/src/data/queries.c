#include "data/queries.h"

#include <glib.h>
#include <stdio.h>

#include "data/catalogs/catalog_reservation.h"
#include "data/catalogs/catalog_user.h"
#include "data/database.h"
#include "data/schemas/flight.h"
#include "data/schemas/reservation.h"
#include "data/schemas/schema_data_types.h"
#include "data/schemas/user.h"
#include "data/schemas/validation/generic_validation.h"
#include "data/statistics/user_flight.h"
#include "data/statistics/user_reservation.h"
#include "io/writing/writer.h"
#include "utils/utilities.h"

static int (*query_functions[])(RowWriter *, Database *, char *) = {
    query_entity_parameters_by_id,
    query_list_user_association,
    query_calculate_average_hotel_rating,
    query_list_hotel_reservations,
    query_list_airport_flights_between_dates,
    query_list_top_aiports_by_passengers_in_year,
    query_list_top_aiports_by_delay_median,
    query_calculate_total_hotel_revenue_between_dates,
    query_list_users_where_name_starts_with_prefix,
    query_database_metrics};

int execute_query_and_save_result(RowWriter *writer, Database *database,
                                  int query_id, char *query_args) {
  return query_functions[query_id](writer, database, query_args);
}

int query_entity_parameters_by_id(RowWriter *writer, Database *database,
                                  char *query_args) {
  if (invalid_integer(query_args)) {
    if (starts_with(query_args, "Book")) {
      return query_reservation_parameters_by_id(writer, database, query_args);
    }
    return query_user_parameters_by_id(writer, database, query_args);
  }
  return query_flight_parameters_by_id(writer, database, query_args);
}

int query_user_parameters_by_id(RowWriter *writer, Database *database,
                                char *query_params) {
  CatalogUser *catalog = database_get_user_catalog(database);
  User *user = catalog_get_user_by_id(catalog, query_params);
  if (user == NULL) return 1;
  if (user_get_account_status(user) == INACTIVE) return 1;

  char *user_id = user_get_id(user);
  char *user_name = user_get_name(user);
  Sex user_sex = user_get_sex(user);
  char *user_sex_string = sex_to_string(user_sex);
  Timestamp user_birth_date = user_get_birth_date(user);
  int user_age = difference_in_years_between_dates(user_birth_date.date,
                                                   SYSTEM_CURRENT_DATE);
  char *user_country_code = user_get_country_code(user);
  char *user_passport = user_get_passport(user);
  int user_number_of_flights =
      get_count_of_flights_belonging_to_user(database, user_id);
  int user_number_of_reservations =
      get_count_of_reservations_belonging_to_user(database, user_id);
  double user_total_spent = get_user_total_spent(database, user_id);
  char *user_total_spent_string = g_strdup_printf("%.3f", user_total_spent);

  char *format[] = {"%s", "%s", "%d", "%s", "%s", "%d", "%d", "%s"};
  char *fields[] = {"name",
                    "sex",
                    "age",
                    "country_code",
                    "passport",
                    "number_of_flights",
                    "number_of_reservations",
                    "total_spent"};

  row_writer_set_formatting(writer, format);
  row_writer_set_field_names(writer, fields);

  write_entity_values(writer, 8, user_name, user_sex_string, user_age,
                      user_country_code, user_passport, user_number_of_flights,
                      user_number_of_reservations, user_total_spent_string);

  g_free(user_id);
  g_free(user_name);
  g_free(user_sex_string);
  g_free(user_country_code);
  g_free(user_passport);
  g_free(user_total_spent_string);
  return 0;
}

int query_flight_parameters_by_id(RowWriter *writer, Database *database,
                                  char *query_args) {
  CatalogFlight *catalog = database_get_flight_catalog(database);
  int flight_id = parse_number(query_args);
  Flight *flight = catalog_get_flight_by_id(catalog, flight_id);
  if (flight == NULL) return 1;

  char *flight_airline = flight_get_airline(flight);
  char *flight_plane_model = flight_get_plane_model(flight);
  char *flight_origin = flight_get_origin(flight);
  char *flight_destination = flight_get_destination(flight);
  Timestamp flight_schedule_departure_date =
      flight_get_schedule_departure_date(flight);
  char *flight_schedule_departure_date_string =
      timestamp_to_string(flight_schedule_departure_date);
  Timestamp flight_schedule_arrival_date =
      flight_get_schedule_arrival_date(flight);
  char *flight_schedule_arrival_date_string =
      timestamp_to_string(flight_schedule_arrival_date);
  int flight_passengers =
      get_count_of_users_belonging_to_flight(database, flight_id);
  Timestamp flight_real_departure_date = flight_get_real_departure_date(flight);
  int flight_delay = difference_in_seconds_between_timestamps(
      flight_schedule_departure_date, flight_real_departure_date);

  char *format[] = {"%s", "%s", "%s", "%s", "%s", "%s", "%d", "%d"};
  char *fields[] = {"airline",
                    "plane_model",
                    "origin",
                    "destination",
                    "schedule_departure_date",
                    "schedule_arrival_date",
                    "passengers",
                    "delay"};

  row_writer_set_formatting(writer, format);
  row_writer_set_field_names(writer, fields);

  write_entity_values(
      writer, 8, flight_airline, flight_plane_model, flight_origin,
      flight_destination, flight_schedule_departure_date_string,
      flight_schedule_arrival_date_string, flight_passengers, flight_delay);

  g_free(flight_airline);
  g_free(flight_plane_model);
  g_free(flight_origin);
  g_free(flight_destination);
  g_free(flight_schedule_departure_date_string);
  g_free(flight_schedule_arrival_date_string);

  return 0;
}

int query_reservation_parameters_by_id(RowWriter *writer, Database *database,
                                       char *query_args) {
  CatalogReservation *catalog = database_get_reservation_catalog(database);
  int reservation_id = parse_number(query_args + 4);
  Reservation *reservation =
      catalog_get_reservation_by_id(catalog, reservation_id);
  if (reservation == NULL) return 1;

  char *reservation_hotel_id = reservation_get_hotel_id(reservation);
  char *reservation_hotel_name = reservation_get_hotel_name(reservation);
  int reservation_hotel_stars = reservation_get_hotel_stars(reservation);
  Timestamp reservation_begin_date = reservation_get_begin_date(reservation);
  char *reservation_begin_date_string = date_to_string(reservation_begin_date);
  Timestamp reservation_end_date = reservation_get_end_date(reservation);
  char *reservation_end_date_string = date_to_string(reservation_end_date);
  bool reservation_includes_breakfast =
      reservation_get_includes_breakfast(reservation);
  int reservation_nights = reservation_get_number_of_nights(reservation);
  double reservation_total_price = reservation_get_total_price(reservation);
  char *reservation_hotel_price_string =
      g_strdup_printf("%.3f", reservation_total_price);

  char *format[] = {"%s", "%s", "%d", "%s", "%s", "%s", "%d", "%s"};
  char *fields[] = {"hotel_id",   "hotel_name", "hotel_stars",
                    "begin_date", "end_date",   "includes_breakfast",
                    "nights",     "total_price"};

  row_writer_set_formatting(writer, format);
  row_writer_set_field_names(writer, fields);

  write_entity_values(writer, 8, reservation_hotel_id, reservation_hotel_name,
                      reservation_hotel_stars, reservation_begin_date_string,
                      reservation_end_date_string,
                      reservation_includes_breakfast ? "True" : "False",
                      reservation_nights, reservation_hotel_price_string);

  g_free(reservation_hotel_id);
  g_free(reservation_hotel_name);
  g_free(reservation_begin_date_string);
  g_free(reservation_end_date_string);
  g_free(reservation_hotel_price_string);

  return 0;
}

int query_list_user_association(RowWriter *writer, Database *database,
                                char *query_args) {
  printf("Query 2 not implemented.\n");
  return -1;
}

int query_calculate_average_hotel_rating(RowWriter *writer, Database *database,
                                         char *query_args) {
  printf("Query 3 not implemented.\n");
  return -1;
}

int query_list_hotel_reservations(RowWriter *writer, Database *database,
                                  char *query_args) {
  char *format[] = {"%s", "%s", "%s", "%s", "%d", "%s"};
  char *fields[] = {"id",      "begin_date", "end_date",
                    "user_id", "rating",     "total_price"};

  row_writer_set_formatting(writer, format);
  row_writer_set_field_names(writer, fields);

  CatalogReservation *catalog = database_get_reservation_catalog(database);
  GPtrArray *reservations = get_hotel_reservations(catalog, query_args);
  int reservations_count = reservations->len;
  g_ptr_array_sort(reservations,
                   compare_reservations_array_elements_by_begin_date);

  for (int i = 0; i < reservations_count; i++) {
    Reservation *reservation = g_ptr_array_index(reservations, i);

    char *reservation_id = reservation_get_id(reservation);
    Timestamp reservation_begin_date = reservation_get_begin_date(reservation);
    char *reservation_begin_date_string =
        date_to_string(reservation_begin_date);
    Timestamp reservation_end_date = reservation_get_end_date(reservation);
    char *reservation_end_date_string = date_to_string(reservation_end_date);
    char *reservation_user_id = reservation_get_user_id(reservation);
    int reservation_rating = reservation_get_rating(reservation);
    double reservation_total_price = reservation_get_total_price(reservation);
    char *reservation_total_price_string =
        g_strdup_printf("%.3f", reservation_total_price);

    write_entity_values(writer, 6, reservation_id,
                        reservation_begin_date_string,
                        reservation_end_date_string, reservation_user_id,
                        reservation_rating, reservation_total_price_string);

    g_free(reservation_id);
    g_free(reservation_begin_date_string);
    g_free(reservation_end_date_string);
    g_free(reservation_user_id);
    g_free(reservation_total_price_string);
  }

  return 0;
}

int query_list_airport_flights_between_dates(RowWriter *writer,
                                             Database *database,
                                             char *query_args) {
  printf("Query 5 not implemented.\n");
  return -1;
}

int query_list_top_aiports_by_passengers_in_year(RowWriter *writer,
                                                 Database *database,
                                                 char *query_args) {
  printf("Query 6 not implemented.\n");
  return -1;
}

int query_list_top_aiports_by_delay_median(RowWriter *writer,
                                           Database *database,
                                           char *query_args) {
  printf("Query 7 not implemented.\n");
  return -1;
}

int query_calculate_total_hotel_revenue_between_dates(RowWriter *writer,
                                                      Database *database,
                                                      char *query_args) {
  printf("Query 8 not implemented.\n");
  return -1;
}

int query_list_users_where_name_starts_with_prefix(RowWriter *writer,
                                                   Database *database,
                                                   char *query_args) {
  printf("Query 9 not implemented.\n");
  return -1;
}

int query_database_metrics(RowWriter *writer, Database *database,
                           char *query_args) {
  printf("Query 10 not implemented.\n");
  return -1;
}