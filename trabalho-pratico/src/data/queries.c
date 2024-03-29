#include "data/queries.h"

#include <glib.h>
#include <stdio.h>

#include "data/catalogs/catalog_passenger.h"
#include "data/catalogs/catalog_reservation.h"
#include "data/catalogs/catalog_user.h"
#include "data/database.h"
#include "data/procedures/sorting.h"
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
    query_list_user_associations,
    query_calculate_average_hotel_rating,
    query_list_hotel_reservations,
    query_list_airport_flights_between_dates,
    query_list_top_airports_by_passengers_in_year,
    query_list_top_airports_by_delay_median,
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
  if (user == NULL || user_get_account_status(user) == INACTIVE) return 1;

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
  row_writer_set_field_names(writer, fields, 8);

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
  unsigned int flight_id = parse_unsigned_integer(query_args);
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
  row_writer_set_field_names(writer, fields, 8);

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
  unsigned int reservation_id = parse_unsigned_integer(query_args + 4);
  Reservation *reservation =
      catalog_get_reservation_by_id(catalog, reservation_id);
  if (reservation == NULL) return 1;

  unsigned short reservation_hotel_id = reservation_get_hotel_id(reservation);
  char *reservation_hotel_id_string =
      g_strdup_printf("HTL%hu", reservation_hotel_id);
  char *reservation_hotel_name = reservation_get_hotel_name(reservation);
  char reservation_hotel_stars = reservation_get_hotel_stars(reservation);
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
  row_writer_set_field_names(writer, fields, 8);

  write_entity_values(writer, 8, reservation_hotel_id_string,
                      reservation_hotel_name, reservation_hotel_stars,
                      reservation_begin_date_string,
                      reservation_end_date_string,
                      reservation_includes_breakfast ? "True" : "False",
                      reservation_nights, reservation_hotel_price_string);

  g_free(reservation_hotel_id_string);
  g_free(reservation_hotel_name);
  g_free(reservation_begin_date_string);
  g_free(reservation_end_date_string);
  g_free(reservation_hotel_price_string);

  return 0;
}

int query_list_user_associations(RowWriter *writer, Database *database,
                                 char *query_args) {
  if (ends_with(query_args, "flights")) {
    query_args[strlen(query_args) - 8] = '\0';
    return query_list_user_flights(writer, database, query_args);
  } else if (ends_with(query_args, "reservations")) {
    query_args[strlen(query_args) - 13] = '\0';
    return query_list_user_reservations(writer, database, query_args);
  }

  CatalogUser *catalog_users = database_get_user_catalog(database);
  User *user = catalog_get_user_by_id(catalog_users, query_args);
  if (user == NULL || user_get_account_status(user) == INACTIVE) return 1;

  char *format[] = {"%s", "%s", "%s"};
  char *fields[] = {"id", "date", "type"};

  row_writer_set_formatting(writer, format);
  row_writer_set_field_names(writer, fields, 3);

  CatalogPassenger *catalog_passengers =
      database_get_passenger_catalog(database);
  GPtrArray *flights = get_user_flights(catalog_passengers, query_args);
  if (flights == NULL) return 1;
  int flights_count = flights->len;
  g_ptr_array_sort(
      flights,
      (GCompareFunc)compare_flights_array_elements_by_schedule_departure_date);

  CatalogReservation *catalog_reservations =
      database_get_reservation_catalog(database);
  GPtrArray *reservations =
      get_user_reservations(catalog_reservations, query_args);
  if (reservations == NULL) return 1;
  int reservations_count = reservations->len;
  g_ptr_array_sort(
      reservations,
      (GCompareFunc)compare_reservations_array_elements_by_begin_date);

  int index_flight = 0;
  int index_reservation = 0;

  while (index_flight < flights_count &&
         index_reservation < reservations_count) {
    Flight *flight = g_ptr_array_index(flights, index_flight);
    Reservation *reservation =
        g_ptr_array_index(reservations, index_reservation);

    Timestamp flight_date = flight_get_schedule_departure_date(flight);
    Timestamp reservation_date = reservation_get_begin_date(reservation);

    if ((flight_date.date >= reservation_date.date)) {
      unsigned int flight_id_int = flight_get_id(flight);
      char *flight_id = g_strdup_printf("%010u", flight_id_int);
      Timestamp flight_schedule_departure_date =
          flight_get_schedule_departure_date(flight);
      char *flight_schedule_departure_date_string =
          date_to_string(flight_schedule_departure_date);
      write_entity_values(writer, 3, flight_id,
                          flight_schedule_departure_date_string, "flight");

      index_flight++;

      g_free(flight_id);
      g_free(flight_schedule_departure_date_string);
    } else if (flight_date.date < reservation_date.date) {
      unsigned int reservation_id_int = reservation_get_id(reservation);
      char *reservation_id = g_strdup_printf("Book%010u", reservation_id_int);
      Timestamp reservation_begin_date =
          reservation_get_begin_date(reservation);
      char *reservation_begin_date_string =
          date_to_string(reservation_begin_date);
      write_entity_values(writer, 3, reservation_id,
                          reservation_begin_date_string, "reservation");

      index_reservation++;

      g_free(reservation_id);
      g_free(reservation_begin_date_string);
    }
  }

  while (index_flight < flights_count) {
    Flight *flight = g_ptr_array_index(flights, index_flight);
    Timestamp flight_date = flight_get_schedule_departure_date(flight);

    unsigned int flight_id_int = flight_get_id(flight);
    char *flight_id = g_strdup_printf("%010u", flight_id_int);
    Timestamp flight_schedule_departure_date =
        flight_get_schedule_departure_date(flight);
    char *flight_schedule_departure_date_string =
        date_to_string(flight_schedule_departure_date);
    write_entity_values(writer, 3, flight_id,
                        flight_schedule_departure_date_string, "flight");

    index_flight++;

    g_free(flight_id);
    g_free(flight_schedule_departure_date_string);
  }

  while (index_reservation < reservations_count) {
    Reservation *reservation =
        g_ptr_array_index(reservations, index_reservation);
    Timestamp reservation_date = reservation_get_begin_date(reservation);

    unsigned int reservation_id_int = reservation_get_id(reservation);
    char *reservation_id = g_strdup_printf("Book%010u", reservation_id_int);
    Timestamp reservation_begin_date = reservation_get_begin_date(reservation);
    char *reservation_begin_date_string =
        date_to_string(reservation_begin_date);
    write_entity_values(writer, 3, reservation_id,
                        reservation_begin_date_string, "reservation");

    index_reservation++;

    g_free(reservation_id);
    g_free(reservation_begin_date_string);
  }

  return 0;
}

int query_list_user_flights(RowWriter *writer, Database *database,
                            char *user_id) {
  CatalogUser *catalog_users = database_get_user_catalog(database);
  User *user = catalog_get_user_by_id(catalog_users, user_id);
  if (user == NULL) return 1;
  if (user_get_account_status(user) == INACTIVE) return 1;

  char *format[] = {"%010u", "%s"};
  char *fields[] = {"id", "date"};

  row_writer_set_formatting(writer, format);
  row_writer_set_field_names(writer, fields, 2);

  CatalogPassenger *catalog_passengers =
      database_get_passenger_catalog(database);
  GPtrArray *flights = get_user_flights(catalog_passengers, user_id);
  if (flights == NULL) return 1;
  int flights_count = flights->len;
  g_ptr_array_sort(
      flights,
      (GCompareFunc)compare_flights_array_elements_by_schedule_departure_date);

  for (int i = 0; i < flights_count; i++) {
    Flight *flight = g_ptr_array_index(flights, i);
    unsigned int flight_id = flight_get_id(flight);
    Timestamp flight_schedule_departure_date =
        flight_get_schedule_departure_date(flight);
    char *flight_schedule_departure_date_string =
        date_to_string(flight_schedule_departure_date);
    write_entity_values(writer, 2, flight_id,
                        flight_schedule_departure_date_string);

    g_free(flight_schedule_departure_date_string);
  }

  return 0;
}

int query_list_user_reservations(RowWriter *writer, Database *database,
                                 char *user_id) {
  CatalogUser *catalog_users = database_get_user_catalog(database);
  User *user = catalog_get_user_by_id(catalog_users, user_id);
  if (user == NULL) return 1;
  if (user_get_account_status(user) == INACTIVE) return 1;

  char *format[] = {"%s", "%s"};
  char *fields[] = {"id", "date"};

  row_writer_set_formatting(writer, format);
  row_writer_set_field_names(writer, fields, 2);

  CatalogReservation *catalog_reservations =
      database_get_reservation_catalog(database);
  GPtrArray *reservations =
      get_user_reservations(catalog_reservations, user_id);
  if (reservations == NULL) return 1;
  int reservations_count = reservations->len;
  g_ptr_array_sort(
      reservations,
      (GCompareFunc)compare_reservations_array_elements_by_begin_date);

  for (int i = 0; i < reservations_count; i++) {
    Reservation *reservation = g_ptr_array_index(reservations, i);
    unsigned int reservation_id_int = reservation_get_id(reservation);
    char *reservation_id = g_strdup_printf("Book%010u", reservation_id_int);
    Timestamp reservation_begin_date = reservation_get_begin_date(reservation);
    char *reservation_begin_date_string =
        date_to_string(reservation_begin_date);
    write_entity_values(writer, 2, reservation_id,
                        reservation_begin_date_string);

    g_free(reservation_id);
    g_free(reservation_begin_date_string);
  }

  return 0;
}

int query_calculate_average_hotel_rating(RowWriter *writer, Database *database,
                                         char *query_args) {
  char *format[] = {"%s"};
  char *fields[] = {"rating"};

  row_writer_set_formatting(writer, format);
  row_writer_set_field_names(writer, fields, 1);

  CatalogReservation *catalog = database_get_reservation_catalog(database);
  unsigned short hotel_id = parse_unsigned_short(query_args + 3);
  GPtrArray *reservations = get_hotel_reservations(catalog, hotel_id);
  int reservations_count = reservations->len;
  double total_rating = 0;
  for (int i = 0; i < reservations_count; i++) {
    Reservation *reservation = g_ptr_array_index(reservations, i);
    char reservation_rating = reservation_get_rating(reservation);
    total_rating += reservation_rating;
  }
  double mean_rating = total_rating / reservations_count;
  char *mean_rating_string = g_strdup_printf("%.3f", mean_rating);

  write_entity_values(writer, 1, mean_rating_string);

  g_free(mean_rating_string);
  return 0;
}

int query_list_hotel_reservations(RowWriter *writer, Database *database,
                                  char *query_args) {
  char *format[] = {"%s", "%s", "%s", "%s", "%d", "%s"};
  char *fields[] = {"id",      "begin_date", "end_date",
                    "user_id", "rating",     "total_price"};

  row_writer_set_formatting(writer, format);
  row_writer_set_field_names(writer, fields, 6);

  CatalogReservation *catalog = database_get_reservation_catalog(database);
  unsigned short hotel_id = parse_unsigned_short(query_args + 3);
  GPtrArray *reservations = get_hotel_reservations(catalog, hotel_id);
  if (reservations == NULL) return 1;
  int reservations_count = reservations->len;
  g_ptr_array_sort(
      reservations,
      (GCompareFunc)compare_reservations_array_elements_by_begin_date);

  for (int i = 0; i < reservations_count; i++) {
    Reservation *reservation = g_ptr_array_index(reservations, i);

    unsigned int reservation_id_int = reservation_get_id(reservation);
    char *reservation_id = g_strdup_printf("Book%010u", reservation_id_int);
    Timestamp reservation_begin_date = reservation_get_begin_date(reservation);
    char *reservation_begin_date_string =
        date_to_string(reservation_begin_date);
    Timestamp reservation_end_date = reservation_get_end_date(reservation);
    char *reservation_end_date_string = date_to_string(reservation_end_date);
    char *reservation_user_id = reservation_get_user_id(reservation);
    char reservation_rating = reservation_get_rating(reservation);
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
  char *format[] = {"%010u", "%s", "%s", "%s", "%s"};
  char *fields[] = {"id", "schedule_departure_date", "destination", "airline",
                    "plane_model"};

  row_writer_set_formatting(writer, format);
  row_writer_set_field_names(writer, fields, 5);

  query_args[46] = '\0';
  char *upper_limit_string = query_args + 27;
  Timestamp upper_limit = parse_timestamp(upper_limit_string);
  query_args[24] = '\0';
  char *lower_limit_string = query_args + 5;
  Timestamp lower_limit = parse_timestamp(lower_limit_string);
  query_args[3] = '\0';

  CatalogFlight *catalog = database_get_flight_catalog(database);
  GPtrArray *flights = get_flights_array(catalog);
  if (flights == NULL) return 1;
  int flights_count = flights->len;
  catalog_sort_flights_by_schedule_departure_date(catalog);
  int lower_bound = find_date_lower_bound_flights(flights, lower_limit);

  for (int i = lower_bound; i < flights_count; i++) {
    Flight *flight = g_ptr_array_index(flights, i);
    char *flight_origin = flight_get_origin(flight);

    if (strcmp(flight_origin, query_args) == 0) {
      Timestamp flight_schedule_departure_date =
          flight_get_schedule_departure_date(flight);

      if (is_timestamp_between_dates(flight_schedule_departure_date,
                                     lower_limit, upper_limit)) {
        unsigned int flight_id = flight_get_id(flight);
        char *flight_schedule_departure_date_string =
            timestamp_to_string(flight_schedule_departure_date);
        char *flight_destination = flight_get_destination(flight);
        char *flight_airline = flight_get_airline(flight);
        char *flight_plane_model = flight_get_plane_model(flight);

        write_entity_values(
            writer, 5, flight_id, flight_schedule_departure_date_string,
            flight_destination, flight_airline, flight_plane_model);

        g_free(flight_schedule_departure_date_string);
        g_free(flight_destination);
        g_free(flight_airline);
        g_free(flight_plane_model);
      }
    }

    g_free(flight_origin);
  }

  return 0;
}

int query_list_top_airports_by_passengers_in_year(RowWriter *writer,
                                                  Database *database,
                                                  char *query_args) {
  char *format[] = {"%s", "%d"};
  char *fields[] = {"name", "passengers"};

  row_writer_set_formatting(writer, format);
  row_writer_set_field_names(writer, fields, 2);

  query_args[4] = '\0';
  int year = parse_number(query_args);
  int N = parse_number(query_args + 5);

  CatalogAirport *catalog = database_get_airport_catalog(database);
  GHashTable *airport_passengers_by_year =
      catalog_get_airport_passengers_by_year(catalog);
  GPtrArray *airport_passengers =
      g_hash_table_lookup(airport_passengers_by_year, GINT_TO_POINTER(year));

  if (airport_passengers == NULL) return 1;
  int airport_passengers_count = airport_passengers->len;

  for (int i = 0; i < N && i < airport_passengers_count; i++) {
    char *airport_id =
        airport_passengers_by_year_get_airport_id(airport_passengers->pdata[i]);
    write_entity_values(writer, 2, airport_id,
                        airport_passengers_by_year_get_passengers(
                            airport_passengers->pdata[i]));
    g_free(airport_id);
  }
  return 0;
}

int query_list_top_airports_by_delay_median(RowWriter *writer,
                                            Database *database,
                                            char *query_args) {
  char *format[] = {"%s", "%d"};
  char *fields[] = {"name", "median"};

  row_writer_set_formatting(writer, format);
  row_writer_set_field_names(writer, fields, 2);

  int N = parse_number(query_args);

  CatalogAirport *catalog = database_get_airport_catalog(database);
  GPtrArray *airport_delays = catalog_get_airport_delays(catalog);
  if (airport_delays == NULL) return 1;
  int airport_delays_count = airport_delays->len;

  for (int i = 0; i < N && i < airport_delays_count; i++) {
    // -1 is the value used to represent an airport with no delays
    if (airport_delay_median_get_delay_median(airport_delays->pdata[i]) == -1) {
      N++;
      continue;
    }

    char *airport_id =
        airport_delay_median_get_airport_id(airport_delays->pdata[i]);
    write_entity_values(
        writer, 2, airport_id,
        airport_delay_median_get_delay_median(airport_delays->pdata[i]));
    g_free(airport_id);
  }
  return 0;
}

int query_calculate_total_hotel_revenue_between_dates(RowWriter *writer,
                                                      Database *database,
                                                      char *query_args) {
  char *format[] = {"%d"};
  char *fields[] = {"revenue"};

  int index = (strchr(query_args + 1, ' ') - (query_args));
  query_args[index] = '\0';
  query_args[index + 11] = '\0';
  Timestamp begin_date = parse_date(query_args + (index + 1));
  Timestamp end_date = parse_date(query_args + (index + 12));

  row_writer_set_formatting(writer, format);
  row_writer_set_field_names(writer, fields, 1);

  CatalogReservation *catalog = database_get_reservation_catalog(database);
  GPtrArray *reservations =
      get_hotel_reservations(catalog, parse_unsigned_short(query_args + 3));
  if (reservations == NULL) return 1;
  int reservations_count = reservations->len;

  qsort_g_ptr_array(
      reservations,
      (GCompareFunc)compare_reservations_array_elements_by_begin_date);

  int revenue = 0;

  for (int i = 0; i < reservations_count; i++) {
    Reservation *reservation =
        (Reservation *)g_ptr_array_index(reservations, i);
    Timestamp reservation_begin = reservation_get_begin_date(reservation);
    Timestamp reservation_end = reservation_get_end_date(reservation);
    if (begin_date.date <= reservation_end.date &&
        end_date.date >= reservation_begin.date) {
      int range_start = (begin_date.date > reservation_begin.date)
                            ? begin_date.date
                            : reservation_begin.date;
      int range_end = (end_date.date < reservation_end.date)
                          ? end_date.date
                          : reservation_end.date;
      int days = range_end - range_start;

      if (reservation_end.date > end_date.date) {
        days++;
      }
      int price_per_night = (int)reservation_get_price_per_night(reservation);
      revenue += (price_per_night * days);
    }
  }

  write_entity_values(writer, 1, revenue);

  return 0;
}

int query_list_users_where_name_starts_with_prefix(RowWriter *writer,
                                                   Database *database,
                                                   char *query_args) {
  char *format[] = {"%s", "%s"};
  char *fields[] = {"id", "name"};

  row_writer_set_formatting(writer, format);
  row_writer_set_field_names(writer, fields, 2);

  CatalogUser *catalog = database_get_user_catalog(database);
  GPtrArray *users = get_users(catalog);
  int users_count = count_users(catalog);

  catalog_sort_users_by_name(catalog);

  int prefix_len = strlen(query_args);
  if (prefix_len >= 2 && query_args[0] == '"' &&
      query_args[prefix_len - 1] == '"') {
    for (int i = 0; i < prefix_len - 1; i++) {
      query_args[i] = query_args[i + 1];
    }
    query_args[prefix_len - 2] = '\0';
  }
  for (int i = 0; i < users_count; i++) {
    User *user = g_ptr_array_index(users, i);

    char *user_name = user_get_name(user);
    AccountStatus status = user_get_account_status(user);
    if (g_str_has_prefix(user_name, query_args) && !status) {
      char *user_id = user_get_id(user);
      write_entity_values(writer, 2, user_id, user_name);
      g_free(user_id);
    }
    g_free(user_name);
  }
  return 0;
}

int query_database_metrics(RowWriter *writer, Database *database,
                           char *query_args) {
  switch (strlen(query_args)) {
    case 0:
      return query_database_metrics_by_years(writer, database);
      break;
    case 4:
      return query_database_metrics_by_months_in_year(writer, database,
                                                      query_args);
      break;
    case 7:
      return query_database_metrics_by_days_in_month(writer, database,
                                                     query_args);
      break;
    default:
      // Error parsing query arguments
      return -1;
      break;
  }
  return 0;
}

int query_database_metrics_by_years(RowWriter *writer, Database *database) {
  char *format[] = {"%d", "%d", "%d", "%d", "%d", "%d"};
  char *fields[] = {
      "year",        "users", "flights", "passengers", "unique_passengers",
      "reservations"};
  row_writer_set_formatting(writer, format);
  row_writer_set_field_names(writer, fields, 6);

  CatalogUser *user_catalog = database_get_user_catalog(database);
  CatalogFlight *flight_catalog = database_get_flight_catalog(database);
  CatalogPassenger *passenger_catalog =
      database_get_passenger_catalog(database);
  CatalogReservation *reservation_catalog =
      database_get_reservation_catalog(database);

  for (int year = 2010; year <= 2023; year++) {
    int users = catalog_get_user_count_by_timestamp_key(user_catalog, year);
    int flights =
        catalog_get_flight_count_by_timestamp_key(flight_catalog, year);
    int passengers =
        catalog_get_passenger_count_by_timestamp_key(passenger_catalog, year);
    int unique_passengers = catalog_get_unique_passenger_count_by_timestamp_key(
        passenger_catalog, year);
    int reservations = catalog_get_reservation_count_by_timestamp_key(
        reservation_catalog, year);
    if (users == 0 && flights == 0 && passengers == 0 &&
        unique_passengers == 0 && reservations == 0)
      continue;
    write_entity_values(writer, 6, year, users, flights, passengers,
                        unique_passengers, reservations);
  }

  return 0;
}

int query_database_metrics_by_months_in_year(RowWriter *writer,
                                             Database *database,
                                             char *query_args) {
  char *format[] = {"%d", "%d", "%d", "%d", "%d", "%d"};
  char *fields[] = {
      "month",       "users", "flights", "passengers", "unique_passengers",
      "reservations"};
  row_writer_set_formatting(writer, format);
  row_writer_set_field_names(writer, fields, 6);

  unsigned short year = parse_unsigned_short(query_args);

  CatalogUser *user_catalog = database_get_user_catalog(database);
  CatalogFlight *flight_catalog = database_get_flight_catalog(database);
  CatalogPassenger *passenger_catalog =
      database_get_passenger_catalog(database);
  CatalogReservation *reservation_catalog =
      database_get_reservation_catalog(database);

  int timestamp_key = year * 100;
  for (int month = 1; month <= 12; month++) {
    timestamp_key++;
    int users =
        catalog_get_user_count_by_timestamp_key(user_catalog, timestamp_key);
    int flights = catalog_get_flight_count_by_timestamp_key(flight_catalog,
                                                            timestamp_key);
    int passengers = catalog_get_passenger_count_by_timestamp_key(
        passenger_catalog, timestamp_key);
    int unique_passengers = catalog_get_unique_passenger_count_by_timestamp_key(
        passenger_catalog, timestamp_key);
    int reservations = catalog_get_reservation_count_by_timestamp_key(
        reservation_catalog, timestamp_key);
    if (users == 0 && flights == 0 && passengers == 0 &&
        unique_passengers == 0 && reservations == 0)
      continue;
    write_entity_values(writer, 6, month, users, flights, passengers,
                        unique_passengers, reservations);
  }

  return 0;
}

int query_database_metrics_by_days_in_month(RowWriter *writer,
                                            Database *database,
                                            char *query_args) {
  char *format[] = {"%d", "%d", "%d", "%d", "%d", "%d"};
  char *fields[] = {
      "day",         "users", "flights", "passengers", "unique_passengers",
      "reservations"};
  row_writer_set_formatting(writer, format);
  row_writer_set_field_names(writer, fields, 6);

  query_args[4] = '\0';

  unsigned short year = parse_unsigned_short(query_args);
  unsigned short month = parse_unsigned_short(query_args + 5);

  CatalogUser *user_catalog = database_get_user_catalog(database);
  CatalogFlight *flight_catalog = database_get_flight_catalog(database);
  CatalogPassenger *passenger_catalog =
      database_get_passenger_catalog(database);
  CatalogReservation *reservation_catalog =
      database_get_reservation_catalog(database);

  int timestamp_key = year * 10000 + month * 100;
  for (int day = 1; day <= 31; day++) {
    timestamp_key++;
    int users =
        catalog_get_user_count_by_timestamp_key(user_catalog, timestamp_key);
    int flights = catalog_get_flight_count_by_timestamp_key(flight_catalog,
                                                            timestamp_key);
    int passengers = catalog_get_passenger_count_by_timestamp_key(
        passenger_catalog, timestamp_key);
    int unique_passengers = catalog_get_unique_passenger_count_by_timestamp_key(
        passenger_catalog, timestamp_key);
    int reservations = catalog_get_reservation_count_by_timestamp_key(
        reservation_catalog, timestamp_key);
    if (users == 0 && flights == 0 && passengers == 0 &&
        unique_passengers == 0 && reservations == 0)
      continue;
    write_entity_values(writer, 6, day, users, flights, passengers,
                        unique_passengers, reservations);
  }

  return 0;
}