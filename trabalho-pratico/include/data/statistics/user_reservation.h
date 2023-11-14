#ifndef STATISTICS_USER_RESERVATION_H
#define STATISTICS_USER_RESERVATION_H

#include <stdbool.h>

#include "data/database.h"

bool validate_reservation_user_association(Database *database, char *user_id);

#endif