#ifndef GENERIC_VALIDATION_H
#define GENERIC_VALIDATION_H

#include "data/schemas/schema_data_types.h"

int empty_error(char* error);

int invalid_date(char* date);

int invalid_timestamp(char* timestamp);

int compare_date(char* start_date, char* end_date);

int compare_timestamp(char* start_timestamp, char* end_timestamp);

#endif