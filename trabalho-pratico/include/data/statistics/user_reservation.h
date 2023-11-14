#ifndef STATISTICS_USER_RESERVATION_H
#define STATISTICS_USER_RESERVATION_H

#include <stdbool.h>

#include "data/database.h"

bool validate_reservation_user_association(Database *database, char *user_id);

int get_count_of_reservations_belonging_to_user(Database *database,
                                                char *user_id);

double get_user_total_spent(Database *database, char *user_id);

#endif