#include "data/queries.h"

#include <stdio.h>

#include "data/database.h"
#include "io/writing/writer.h"

static int (*query_functions[])(RowWriter *, Database *, char *) = {
    query_find_entity_by_id,
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

int query_find_entity_by_id(RowWriter *writer, Database *database,
                            char *query_args) {
  printf("Query 1 not implemented.\n");
  return -1;
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
  printf("Query 4 not implemented.\n");
  return -1;
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