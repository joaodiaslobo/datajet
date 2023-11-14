#ifndef QUERIES_H
#define QUERIES_H

#include "data/database.h"
#include "io/writing/writer.h"

#define SYSTEM_CURRENT_DATE 20231001

int execute_query_and_save_result(RowWriter *writer, Database *database,
                                  int query_id, char *query_args);

int query_entity_parameters_by_id(RowWriter *writer, Database *database,
                                  char *query_args);

int query_user_parameters_by_id(RowWriter *writer, Database *database,
                                char *user_id);

int query_flight_parameters_by_id(RowWriter *writer, Database *database,
                                  char *query_args);

int query_list_user_association(RowWriter *writer, Database *database,
                                char *query_args);

int query_calculate_average_hotel_rating(RowWriter *writer, Database *database,
                                         char *query_args);

int query_list_hotel_reservations(RowWriter *writer, Database *database,
                                  char *query_args);

int query_list_airport_flights_between_dates(RowWriter *writer,
                                             Database *database,
                                             char *query_args);

int query_list_top_aiports_by_passengers_in_year(RowWriter *writer,
                                                 Database *database,
                                                 char *query_args);

int query_list_top_aiports_by_delay_median(RowWriter *writer,
                                           Database *database,
                                           char *query_args);

int query_calculate_total_hotel_revenue_between_dates(RowWriter *writer,
                                                      Database *database,
                                                      char *query_args);

int query_list_users_where_name_starts_with_prefix(RowWriter *writer,
                                                   Database *database,
                                                   char *query_args);

int query_database_metrics(RowWriter *writer, Database *database,
                           char *query_args);

#endif