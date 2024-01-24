/**
 * @file queries.h
 * @brief Implementation of queries available for the application database.
 */
#ifndef QUERIES_H
#define QUERIES_H

#include "data/database.h"
#include "io/writing/writer.h"

#define SYSTEM_CURRENT_DATE 20231001

typedef struct queryDefinition {
  char *name;
  char *description;
  int min_args;
  int max_args;
} QueryDefinition;

static const QueryDefinition query_definitions[10] = {
    {"List general information about an entity",
     "Lists general information about an entity (user, flight or reservation) "
     "associated with the identifier passed in the query arguments.",
     1, 1},
    {"List user associations",
     "Lists all user associations (flights and reservations) sorted by date "
     "(most recent to oldest). Optionally, the second argument can filter the "
     "associations by type.",
     1, 2},
    {"Calculate average hotel rating",
     "Calculates the average rating of a hotel via its identifier.", 1, 1},
    {"List hotel reservations",
     "Lists all reservations associated with a hotel sorted by date (most "
     "recent to oldest) based on the identifier passed in the query arguments.",
     1, 1},
    {"List airport flights between dates",
     "Lists flights that departed from a certain origin airport between two "
     "dates sorted by departure date (oldest to most recent).",
     3, 3},
    {"List top airports by passengers in a year",
     "Lists top airports by most passengers in a given year.", 1, 1},
    {"List top airports by delay medians",
     "Lists top airports by highest delay median.", 1, 1},
    {"Calculate total hotel revenue between dates",
     "Calculates the total revenue of a certain hotel made between two dates.",
     3, 3},
    {"List users whose name starts with prefix",
     "Lists all users whose name starts with a certain prefix sorted by "
     "alphabetical order.",
     1, 1},
    {"List database metrics",
     "Lists general application metrics such as number of users, number of "
     "flights, number of passengers (repeated and unique) and number of "
     "reservations. Aggregates can be filtered by year or year and month. If "
     "no arguments are provided metrics are generated for all years where data "
     "is found.",
     0, 2}};

/**
 * @brief Executes a query and saves the result.
 * @details Executes a query and saves the result to a file.
 *
 * @param writer Writer to be used to write the result.
 * @param database Main database.
 * @param query_id Query id.
 * @param query_args Query arguments.
 * @return 0 if the execution succeeded, 1 if it failed and -1 if the query
 * hasn't been implemented.
 */
int execute_query_and_save_result(RowWriter *writer, Database *database,
                                  int query_id, char *query_args);

/**
 * @brief Lists general information about an entity.
 * @details Lists general information about an entity associated with the
 * identifier passed in the query arguments.
 *
 * @param writer Writer to be used to write the result.
 * @param database Main database.
 * @param query_args Query arguments.
 * @return 0 if the execution succeeded, 1 if it failed.
 */
int query_entity_parameters_by_id(RowWriter *writer, Database *database,
                                  char *query_args);

/**
 * @brief Lists general information about a user.
 * @details Lists general information about a user associated with the
 * identifier passed in the query arguments.
 *
 * @param writer Writer to be used to write the result.
 * @param database Main database.
 * @param query_args Query arguments.
 * @return 0 if the execution succeeded, 1 if it failed.
 */
int query_user_parameters_by_id(RowWriter *writer, Database *database,
                                char *user_id);

/**
 * @brief Lists general information about a flight.
 * @details Lists general information about a flight associated with the
 * identifier passed in the query arguments.
 *
 * @param writer Writer to be used to write the result.
 * @param database Main database.
 * @param query_args Query arguments.
 * @return 0 if the execution succeeded, 1 if it failed.
 */
int query_flight_parameters_by_id(RowWriter *writer, Database *database,
                                  char *query_args);

/**
 * @brief Lists general information about a reservation.
 * @details Lists general information about a reservation associated with the
 * identifier passed in the query arguments.
 *
 * @param writer Writer to be used to write the result.
 * @param database Main database.
 * @param query_args Query arguments.
 * @return 0 if the execution succeeded, 1 if it failed.
 */
int query_reservation_parameters_by_id(RowWriter *writer, Database *database,
                                       char *query_args);

/**
 * @brief Lists user associations.
 * @details Lists all user associations organized by date (most recent to
 * oldest) of certain type(s) depending on the second argument.
 *
 * @param writer Writer to be used to write the result.
 * @param database Main database.
 * @param query_args Query arguments.
 * @return 0 if the execution succeeded, 1 if it failed.
 */
int query_list_user_associations(RowWriter *writer, Database *database,
                                 char *query_args);

/**
 * @brief Lists user flights.
 * @details Lists all flights organized by date (most recent to oldest) of an
 * user.
 *
 * @param writer Writer to be used to write the result.
 * @param database Main database.
 * @param user_id User id.
 * @return 0 if the execution succeeded, 1 if it failed.
 */
int query_list_user_flights(RowWriter *writer, Database *database,
                            char *user_id);

/**
 * @brief Lists user reservations.
 * @details Lists all reservations organized by date (most recent to oldest) of
 * an user.
 *
 * @param writer Writer to be used to write the result.
 * @param database Main database.
 * @param user_id User id.
 * @return 0 if the execution succeeded, 1 if it failed.
 */
int query_list_user_reservations(RowWriter *writer, Database *database,
                                 char *user_id);

/**
 * @brief Calculates average hotel rating.
 * @details Calculates the average rating of a hotel.
 *
 * @param writer Writer to be used to write the result.
 * @param database Main database.
 * @param query_args Query arguments.
 * @return 0 if the execution succeeded, 1 if it failed.
 */
int query_calculate_average_hotel_rating(RowWriter *writer, Database *database,
                                         char *query_args);

/**
 * @brief Lists all reservations associated with a hotel.
 * @details Lists all reservations associated with a hotel based on the
 * identifier passed in the query arguments.
 *
 * @param writer Writer to be used to write the result.
 * @param database Main database.
 * @param query_args Query arguments.
 * @return 0 if the execution succeeded, 1 if it failed.
 */
int query_list_hotel_reservations(RowWriter *writer, Database *database,
                                  char *query_args);

/**
 * @brief Lists airport flights between dates.
 * @details Lists flights that departed from a certain origin airport between
 * two dates.
 *
 * @param writer Writer to be used to write the result.
 * @param database Main database.
 * @param user_id Query arguments.
 * @return 0 if the execution succeeded, 1 if it failed.
 */
int query_list_airport_flights_between_dates(RowWriter *writer,
                                             Database *database,
                                             char *query_args);

/**
 * @brief Lists top airports by passengers in a year.
 * @details Lists top airports by passengers in a year.
 *
 * @param writer Writer to be used to write the result.
 * @param database Main database.
 * @param user_id Query arguments.
 * @return 0 if the execution succeeded, 1 if it failed.
 */
int query_list_top_airports_by_passengers_in_year(RowWriter *writer,
                                                  Database *database,
                                                  char *query_args);

/**
 * @brief Lists top airports by delay median.
 * @details Lists top airports by their delay median comparing flights' schedule
 * and real departure dates that departed from a certain origin airport.
 *
 * @param writer Writer to be used to write the result.
 * @param database Main database.
 * @param user_id Query arguments.
 * @return 0 if the execution succeeded, 1 if it failed.
 */
int query_list_top_airports_by_delay_median(RowWriter *writer,
                                            Database *database,
                                            char *query_args);

/**
 * @brief Calculates total hotel revenue between dates.
 * @details Calculates total revenue of a certain hotel made between two dates.
 *
 * @param writer Writer to be used to write the result.
 * @param database Main database.
 * @param user_id Query arguments.
 * @return 0 if the execution succeeded, 1 if it failed.
 */
int query_calculate_total_hotel_revenue_between_dates(RowWriter *writer,
                                                      Database *database,
                                                      char *query_args);

/**
 * @brief Lists users where name starts with prefix.
 * @details Lists all users whose names starts with a certain prefix.
 *
 * @param writer Writer to be used to write the result.
 * @param database Main database.
 * @param query_args Query arguments.
 * @return 0 if the execution succeeded, 1 if it failed.
 */
int query_list_users_where_name_starts_with_prefix(RowWriter *writer,
                                                   Database *database,
                                                   char *query_args);

/**
 * @brief List database metrics.
 * @details Lists database metrics.
 *
 * @param writer Writer to be used to write the result.
 * @param database Main database.
 * @param query_args Query arguments.
 * @return 0 if the execution succeeded, 1 if it failed.
 */
int query_database_metrics(RowWriter *writer, Database *database,
                           char *query_args);

/**
 * @brief List database metrics by years.
 * @details Lists database metrics by all years contained in the database.
 *
 * @param writer Writer to be used to write the result.
 * @param database Main database.
 * @return 0 if the execution succeeded, 1 if it failed.
 *
 */
int query_database_metrics_by_years(RowWriter *writer, Database *database);

/**
 * @brief List database metrics by months in a year.
 * @details Lists database metrics by all months in a specific year contained in
 * the database.
 *
 * @param writer Writer to be used to write the result.
 * @param database Main database.
 * @return 0 if the execution succeeded, 1 if it failed.
 *
 */
int query_database_metrics_by_months_in_year(RowWriter *writer,
                                             Database *database,
                                             char *query_args);
/**
 * @brief List database metrics by days in a month.
 * @details Lists database metrics by all days in a specific month from a
 * specific year contained in the database.
 *
 * @param writer Writer to be used to write the result.
 * @param database Main database.
 * @return 0 if the execution succeeded, 1 if it failed.
 *
 */
int query_database_metrics_by_days_in_month(RowWriter *writer,
                                            Database *database,
                                            char *query_args);

#endif