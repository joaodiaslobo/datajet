#ifndef GENERIC_VALIDATION_H
#define GENERIC_VALIDATION_H

#include "data/schemas/schema_data_types.h"

bool is_empty_value(char* value);

bool invalid_date(char* date);

bool invalid_timestamp(char* timestamp);

bool compare_date(char* start_date, char* end_date);

bool compare_timestamp(char* start_timestamp, char* end_timestamp);

bool invalid_value_length(int length, char* value);

bool invalid_bool_value(char* value);

bool invalid_positive_integer(char* value);

#endif