#ifndef SCHEMA_UTILITIES_H
#define SCHEMA_UTILITIES_H

typedef enum sex { F = 0, M = 1 } Sex;

typedef struct date {
  int timestamp;
} Date;

typedef enum pay_method { CASH = 0, CREDIT = 1, DEBIT = 2 } PayMethod;

typedef enum account_status { ACTIVE = 0, INACTIVE = 1 } AccountStatus;

#endif