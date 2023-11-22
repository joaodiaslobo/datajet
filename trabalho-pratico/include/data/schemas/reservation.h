/**
 * @file reservation.h
 * @brief Reservation schema.
 */
#ifndef RESERVATION_H
#define RESERVATION_H

#include <glib.h>
#include <stdbool.h>

#include "data/schemas/schema_data_types.h"
#include "io/parsing/reader.h"

typedef struct reservation Reservation;

/**
 * @brief Creates reservation.
 * @details Initializes reservation parameters, creating a new reservation.
 *
 * @param id Hotel id.
 * @param user_id User id.
 * @param hotel_id Hotel id.
 * @param hotel_name Hotel name.
 * @param hotel_stars Hotel stars.
 * @param city_tax City tax.
 * @param address Address.
 * @param begin_date Begin date.
 * @param end_date End date.
 * @param price_per_night Price per night.
 * @param includes_breakfast Includes breakfast.
 * @param room_details Room details.
 * @param rating Rating.
 * @param comment Comment.
 * @return New reservation.
 */
Reservation* create_reservation(unsigned short id, char* user_id,
                                char* hotel_id, char* hotel_name,
                                int hotel_stars, int city_tax, char* address,
                                Timestamp begin_date, Timestamp end_date,
                                int price_per_night, bool includes_breakfast,
                                char* room_details, int rating, char* comment);

/**
 * @brief Frees reservation.
 * @param reservation_ptr Reservation pointer.
 */
void free_reservation(void* reservation_ptr);

/**
 * @brief Parses reservation and add to catalog.
 * @param reader Reader to be used to read the datasets.
 * @param catalog
 * @param database Main database.
 * @return 0 if the execution succeeded, 1 if it failed.
 */
int parse_reservation_and_add_to_catalog(RowReader* reader, void* catalog,
                                         void* database);
/**
 * @brief Indicates if a reservation association is invalid or not.
 * @param database Main database.
 * @param user_id User id.
 * @return true if invalid, false if valid.
 */
bool reservation_invalid_association(void* database, char* user_id);

/**
 * @brief Gets reservation's id.
 * @param reservation Reservation.
 * @return Reservation's id.
 */
unsigned short reservation_get_id(Reservation* reservation);

/**
 * @brief Gets reservation's user id.
 * @param reservation Reservation.
 * @return Reservation's user id.
 */
char* reservation_get_user_id(Reservation* reservation);

/**
 * @brief Gets reservation's hotel id.
 * @param reservation Reservation.
 * @return Reservation's hotel id.
 */
char* reservation_get_hotel_id(Reservation* reservation);

/**
 * @brief Gets reservation's hotel name.
 * @param reservation Reservation.
 * @return Reservation's hotel name.
 */
char* reservation_get_hotel_name(Reservation* reservation);

/**
 * @brief Gets reservation's hotel stars.
 * @param reservation Reservation.
 * @return Reservation's hotel stars.
 */
int reservation_get_hotel_stars(Reservation* reservation);

/**
 * @brief Gets reservation's city tax.
 * @param reservation Reservation.
 * @return Reservation's city tax.
 */
int reservation_get_city_tax(Reservation* reservation);

/**
 * @brief Gets reservation's address.
 * @param reservation Reservation.
 * @return Reservation's address.
 */
char* reservation_get_address(Reservation* reservation);

/**
 * @brief Gets reservation's begin date.
 * @param reservation Reservation.
 * @return Reservation's begin date.
 */
Timestamp reservation_get_begin_date(Reservation* reservation);

/**
 * @brief Gets reservation's end date.
 * @param reservation Reservation.
 * @return Reservation's end date.
 */
Timestamp reservation_get_end_date(Reservation* reservation);

/**
 * @brief Gets reservation's price per night.
 * @param reservation Reservation.
 * @return Reservation's price per night.
 */
int reservation_get_price_per_night(Reservation* reservation);

/**
 * @brief Gets reservation's includes breakfast bool.
 * @param reservation Reservation.
 * @return true if it includes breakfast, false if not.
 */
bool reservation_get_includes_breakfast(Reservation* reservation);

/**
 * @brief Gets reservation's room details.
 * @param reservation Reservation.
 * @return Reservation's room details.
 */
char* reservation_get_room_details(Reservation* reservation);

/**
 * @brief Gets reservation's rating.
 * @param reservation Reservation.
 * @return Reservation's rating.
 */
int reservation_get_rating(Reservation* reservation);

/**
 * @brief Gets reservation's comment.
 * @param reservation Reservation.
 * @return Reservation's comment.
 */
char* reservation_get_comment(Reservation* reservation);

/**
 * @brief Gets reservation's number of nights.
 * @param reservation Reservation.
 * @return Reservation's number of nights.
 */
int reservation_get_number_of_nights(Reservation* reservation);

/**
 * @brief Gets reservation's total price.
 * @param reservation Reservation.
 * @return Reservation's total price.
 */
double reservation_get_total_price(Reservation* reservation);

#endif